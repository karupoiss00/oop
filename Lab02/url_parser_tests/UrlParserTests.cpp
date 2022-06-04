#include <catch2/catch.hpp>
#include <string>
#include "../url_parser/UrlParser.h"

using namespace std;

TEST_CASE("domain parsing")
{
	Protocol protocol;
	unsigned port;
	string host;
	string document;

	SECTION("[Correct] ip address parsing")
	{
		const string url = "http://127.0.0.1/";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::HTTP);
		REQUIRE(port == 80);
		REQUIRE(host == "127.0.0.1");
		REQUIRE(document == "");
	}

	SECTION("[Correct] localhost parsing")
	{
		const string url = "ftp://localhost/";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::FTP);
		REQUIRE(port == 21);
		REQUIRE(host == "localhost");
		REQUIRE(document == "");
	}

	SECTION("[Incorrect] hasn't domain")
	{
		const string url = "https://:8000/documentLevel1/documentLevel2/index.html";
		const bool result = ParseURL(url, protocol, port, host, document);
		REQUIRE(!result);
	}

	SECTION("[Incorrect] domain as dot")
	{
		const string url = "https://.:8000/documentLevel1/documentLevel2/index.html";
		const bool result = ParseURL(url, protocol, port, host, document);
		REQUIRE(!result);
	}
}

TEST_CASE("port parsing test")
{
	Protocol protocol;
	unsigned port;
	string host;
	string document;

	SECTION("[Correct] Max port value")
	{
		const string url = "ftp://localhost:65535/documentLevel1/documentLevel2/index.html";
		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::FTP);
		REQUIRE(port == 65535);
		REQUIRE(host == "localhost");
		REQUIRE(document == "documentLevel1/documentLevel2/index.html");
	}

	SECTION("[Correct] Min port value")
	{
		const string url = "ftp://localhost:1/documentLevel1/documentLevel2/index.html";
		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::FTP);
		REQUIRE(port == 1);
		REQUIRE(host == "localhost");
		REQUIRE(document == "documentLevel1/documentLevel2/index.html");
	}

	SECTION("[Incorrect] Port is bigger than max port value")
	{
		const string urlPortOutOfRange = "https://oop.com:65536/";
		const bool resultPortOutOfRange = ParseURL(urlPortOutOfRange, protocol, port, host, document);
		REQUIRE(!resultPortOutOfRange);
	}

	SECTION("[Incorrect] Port is smaller than min port value")
	{
		const string urlPortOutOfRange = "https://oop.com:0/";
		const bool resultPortOutOfRange = ParseURL(urlPortOutOfRange, protocol, port, host, document);
		REQUIRE(!resultPortOutOfRange);
	}

	SECTION("[Incorrect] Port has chars")
	{
		const string urlPortOutOfRange = "https://oop.com:1abc/";
		const bool resultPortOutOfRange = ParseURL(urlPortOutOfRange, protocol, port, host, document);
		REQUIRE(!resultPortOutOfRange);
	}
}

TEST_CASE("protocol parsing test")
{
	Protocol protocol;
	unsigned port;
	string host;
	string document;

	SECTION("[Correct] https parsing")
	{
		const string url = "hTTps://localhost:8000/documentLevel1/documentLevel2/index.html";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(port == 8000);
		REQUIRE(host == "localhost");
		REQUIRE(document == "documentLevel1/documentLevel2/index.html");
	}

	SECTION("[Correct] http parsing")
	{
		const string url = "HTTP://localhost:8000/documentLevel1/documentLevel2/index.html";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::HTTP);
		REQUIRE(port == 8000);
		REQUIRE(host == "localhost");
		REQUIRE(document == "documentLevel1/documentLevel2/index.html");
	}

	SECTION("[Correct] ftp parsing")
	{
		const string url = "fTp://localhost:8000/documentLevel1/documentLevel2/index.html";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::FTP);
		REQUIRE(port == 8000);
		REQUIRE(host == "localhost");
		REQUIRE(document == "documentLevel1/documentLevel2/index.html");
	}

	SECTION("[Incorrect] incorrect protocol parsing")
	{
		const string url = "abc://localhost:8000/documentLevel1/documentLevel2/index.html";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(!result);
	}
}

TEST_CASE("auto set port by protocol")
{
	Protocol protocol;
	unsigned port;
	string host;
	string document;

	SECTION("https port test")
	{
		const string url = "https://localhost/doc/";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(port == 443);
		REQUIRE(host == "localhost");
		REQUIRE(document == "doc/");
	}

	SECTION("http port test")
	{
		const string url = "http://localhost/doc/";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::HTTP);
		REQUIRE(port == 80);
		REQUIRE(host == "localhost");
		REQUIRE(document == "doc/");
	}

	SECTION("ftp port test")
	{
		const string url = "ftp://localhost/doc/";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::FTP);
		REQUIRE(port == 21);
		REQUIRE(host == "localhost");
		REQUIRE(document == "doc/");
	}
}

TEST_CASE("document parsing")
{
	Protocol protocol;
	unsigned port;
	string host;
	string document;

	SECTION("document parsing test")
	{
		const string url = "https://oop.com:8000/documentLevel1/documentLevel2/index.html";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(port == 8000);
		REQUIRE(host == "oop.com");
		REQUIRE(document == "documentLevel1/documentLevel2/index.html");
	}


	SECTION("port value as document")
	{
		const string url = "https://localhost/:8000";

		const bool result = ParseURL(url, protocol, port, host, document);

		REQUIRE(result);
		REQUIRE(protocol == Protocol::HTTPS);
		REQUIRE(port == 443);
		REQUIRE(host == "localhost");
		REQUIRE(document == ":8000");
	}
}