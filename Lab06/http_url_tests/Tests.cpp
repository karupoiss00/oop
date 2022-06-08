#include <catch2/catch.hpp>
#include <string>
#include <vector>
#include "../http_url/CHttpUrl.h"

using namespace std;

struct ExpectedUrlState
{
	ExpectedUrlState
	(
		Protocol protocol,
		string const& domain,
		unsigned short port,
		string const& document
	) : m_protocol(protocol), m_document(document), m_domain(domain), m_port(port) {};
	
	void isEqual(CHttpUrl const& url)
	{
		CHECK(url.GetDocument() == m_document);
		CHECK(url.GetDomain() == m_domain);
		CHECK(url.GetPort() == m_port);
		CHECK(url.GetProtocol() == m_protocol);
	}

	Protocol m_protocol;
	string m_domain;
	string m_document;
	unsigned short m_port;
};

struct CHttpUrlFixture
{
	CHttpUrlFixture(ExpectedUrlState expected, vector<CHttpUrl> recieves)
		: m_expected(expected), m_recieves(recieves)
	{

	}

	void Test()
	{
		for (const auto recieved : m_recieves)
		{
			m_expected.isEqual(recieved);
		}
	}

	ExpectedUrlState m_expected;
	vector<CHttpUrl> m_recieves;
};

TEST_CASE("domain parsing")
{

	SECTION("ip address parsing")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTP, "127.0.0.1", 80, "/"),
			{
				CHttpUrl("http://127.0.0.1/"),
				CHttpUrl("127.0.0.1", "/"),
				CHttpUrl("127.0.0.1", "/", Protocol::HTTP, 80),
			}
		);

		fixture.Test();
	}

	SECTION("localhost parsing")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTPS, "localhost", 443, "/"),
			{
				CHttpUrl("https://localhost/"),
				CHttpUrl("localhost", "/", Protocol::HTTPS),
				CHttpUrl("localhost", "/", Protocol::HTTPS, 443),
			}
		);

		fixture.Test();
	}

	SECTION("1 level domain parsing")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTPS, "oop.com", 443, "/"),
			{
				CHttpUrl("https://oop.com/"),
				CHttpUrl("oop.com", "/", Protocol::HTTPS),
				CHttpUrl("oop.com", "/", Protocol::HTTPS, 443),
			}
		);

		fixture.Test();
	}

	SECTION("2 level domain parsing")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTPS, "oop.ood.com", 443, "/"),
			{
				CHttpUrl("https://oop.ood.com/"),
				CHttpUrl("oop.ood.com", "/", Protocol::HTTPS),
				CHttpUrl("oop.ood.com", "/", Protocol::HTTPS, 443),
			}
		);
		fixture.Test();
	}

	SECTION("3 level domain parsing")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTPS, "oop.ood.gamedev.com", 443, "/"),
			{
				CHttpUrl("https://oop.ood.gamedev.com/"),
				CHttpUrl("oop.ood.gamedev.com", "/", Protocol::HTTPS),
				CHttpUrl("oop.ood.gamedev.com", "/", Protocol::HTTPS, 443),
			}
		);
		fixture.Test();
	}

	SECTION("hasn't domain")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl("https://");
			}()
		);
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl("", "/");
			}()
		);
	}

	SECTION("domain as dot")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl("https://.");
			}()
		);
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl("...", "/");
			}()
		);
	}
}

TEST_CASE("port parsing")
{
	SECTION("max port value")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTP, "oop.com", 65535, "/"),
			{
				CHttpUrl("http://oop.com:65535/"),
				CHttpUrl("oop.com", "/", Protocol::HTTP, 65535),
			}
		);
		fixture.Test();
	}

	SECTION("min port value")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTP, "oop.com", 1, "/"),
			{
				CHttpUrl("http://oop.com:1/"),
				CHttpUrl("oop.com", "/", Protocol::HTTP, 1),
			}
		);
		fixture.Test();
	}

	SECTION("bigger when max port value")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl("https://oop.com:65536/");	
			}()
		);

		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl("oop.com", "/", Protocol::HTTPS, Port(65536));
			}()
		);
	}

	SECTION("smaller when min port value")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl("http://oop.com:0/");
			}()
		);
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl("oop.com", "/", Protocol::HTTPS, 0);
			}()
		);
	}

	SECTION("port has chars")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl recieved("http://oop.com:chars/");
			}()
		);
	}
}

TEST_CASE("protocol parsing test")
{
	SECTION("https parsing")
	{
		ExpectedUrlState expected(Protocol::HTTPS, "oop.com", 443, "/");
		CHttpUrl recieved("https://oop.com/");

		expected.isEqual(recieved);
	}
	
	SECTION("http parsing")
	{
		ExpectedUrlState expected(Protocol::HTTP, "oop.com", 80, "/");
		CHttpUrl recieved("http://oop.com/");

		expected.isEqual(recieved);
	}

	SECTION("unknown protocol")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl recieved("ftp://oop.com/");
			}()
		);
	}
}

TEST_CASE("document parsing")
{
	SECTION("document parsing test")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTP, "oop.com", 80, "/documentLevel1/documentLevel2/index.html"),
			{
				CHttpUrl("http://oop.com/documentLevel1/documentLevel2/index.html"),
				CHttpUrl("oop.com", "documentLevel1/documentLevel2/index.html", Protocol::HTTP, 80),
			}
		);

		fixture.Test();
	}


	SECTION("port value as document")
	{
		CHttpUrlFixture fixture
		(
			ExpectedUrlState(Protocol::HTTP, "oop.com", 80, "/:8000"),
			{
				CHttpUrl("http://oop.com/:8000"),
				CHttpUrl("oop.com", ":8000", Protocol::HTTP, 80),
			}
		);

		fixture.Test();
	}
}

TEST_CASE("GetUrl tests")
{
	SECTION("default HTTP port")
	{
		string expectedUrl = "http://oop.com/documentLevel1/documentLevel2/index.html";
		CHttpUrl url("http://oop.com:80/documentLevel1/documentLevel2/index.html");

		CHECK(url.GetURL() == expectedUrl);
	}

	SECTION("default HTTPS port")
	{
		string expectedUrl = "https://oop.com/documentLevel1/documentLevel2/index.html";
		CHttpUrl url("https://oop.com:443/documentLevel1/documentLevel2/index.html");

		CHECK(url.GetURL() == expectedUrl);
	}

	SECTION("custom HTTP port")
	{
		string expectedUrl = "http://oop.com:8000/documentLevel1/documentLevel2/index.html";
		CHttpUrl url("http://oop.com:8000/documentLevel1/documentLevel2/index.html");

		CHECK(url.GetURL() == expectedUrl);
	}

	SECTION("custom HTTPS port")
	{
		string expectedUrl = "https://oop.com:8000/documentLevel1/documentLevel2/index.html";
		CHttpUrl url("https://oop.com:8000/documentLevel1/documentLevel2/index.html");

		CHECK(url.GetURL() == expectedUrl);
	}

	SECTION("no document")
	{
		string expectedUrl = "https://oop.com:8000/";
		CHttpUrl url("https://oop.com:8000");

		CHECK(url.GetURL() == expectedUrl);
	}
}