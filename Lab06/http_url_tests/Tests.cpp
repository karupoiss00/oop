#include <catch2/catch.hpp>
#include <string>
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
	
	void isEqual(CHttpUrl url)
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

TEST_CASE("domain parsing")
{

	SECTION("ip address parsing")
	{
		ExpectedUrlState expected(Protocol::HTTP, "127.0.0.1", 80, "/");
		CHttpUrl recieved("http://127.0.0.1/");

		expected.isEqual(recieved);
	}

	SECTION("localhost parsing")
	{
		ExpectedUrlState expected(Protocol::HTTPS, "localhost", 443, "/");
		CHttpUrl recieved("https://localhost/");
		expected.isEqual(recieved);
	}

	SECTION("1 level domain parsing")
	{
		ExpectedUrlState expected(Protocol::HTTPS, "oop.com", 443, "/");
		CHttpUrl recieved("https://oop.com/");
		expected.isEqual(recieved);
	}

	SECTION("2 level domain parsing")
	{
		ExpectedUrlState expected(Protocol::HTTPS, "oop.ood.com", 443, "/");
		CHttpUrl recieved("https://oop.ood.com/");
		expected.isEqual(recieved);
	}

	SECTION("3 level domain parsing")
	{
		ExpectedUrlState expected(Protocol::HTTPS, "oop.ood.gamedev.com", 443, "/");
		CHttpUrl recieved("https://oop.ood.gamedev.com/");
		expected.isEqual(recieved);
	}

	SECTION("hasn't domain")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl recieved("https://");
			}()
		);
	}

	SECTION("domain as dot")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl recieved("https://.");
			}()
		);
	}
}

TEST_CASE("port parsing")
{
	SECTION("max port value")
	{
		ExpectedUrlState expected(Protocol::HTTP, "oop.com", 65535, "/");
		CHttpUrl recieved("http://oop.com:65535/");

		expected.isEqual(recieved);
	}

	SECTION("min port value")
	{
		ExpectedUrlState expected(Protocol::HTTP, "oop.com", 1, "/");
		CHttpUrl recieved("http://oop.com:1/");

		expected.isEqual(recieved);
	}

	SECTION("bigger when max port value")
	{
		CHECK_THROWS
		(
			[]()
			{
			CHttpUrl recieved("http://oop.com:65536/");
			}()
		);
	}

	SECTION("smaller when min port value")
	{
		CHECK_THROWS
		(
			[]()
			{
				CHttpUrl recieved("http://oop.com:0/");
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
		ExpectedUrlState expected(Protocol::HTTP, "oop.com", 80, "/documentLevel1/documentLevel2/index.html");
		CHttpUrl recieved("http://oop.com/documentLevel1/documentLevel2/index.html");

		expected.isEqual(recieved);
	}


	SECTION("port value as document")
	{
		ExpectedUrlState expected(Protocol::HTTP, "oop.com", 80, "/:8000");
		CHttpUrl recieved("http://oop.com/:8000");

		expected.isEqual(recieved);
	}
}