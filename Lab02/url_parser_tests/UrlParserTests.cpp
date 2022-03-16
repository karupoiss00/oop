#include <catch2/catch.hpp>
#include <string>
#include "../url_parser/UrlParser.h"

using namespace std;

TEST_CASE("ip test")
{
	const string url = "http://127.0.0.1/";

	Protocol protocol;
	unsigned port;
	string host;
	string document;

	const bool result = ParseURL(url, protocol, port, host, document);

	REQUIRE(result);
	REQUIRE(protocol == Protocol::HTTP);
	REQUIRE(port == 80);
	REQUIRE(host == "127.0.0.1");
	REQUIRE(document == "");
}

TEST_CASE("localhost test")
{
	const string url = "ftp://localhost/";

	Protocol protocol;
	unsigned port;
	string host;
	string document;

	const bool result = ParseURL(url, protocol, port, host, document);

	REQUIRE(result);
	REQUIRE(protocol == Protocol::FTP);
	REQUIRE(port == 21);
	REQUIRE(host == "localhost");
	REQUIRE(document == "");
}

TEST_CASE("auto set for https port test")
{
	const string url = "https://localhost/doc/";

	Protocol protocol;
	unsigned port;
	string host;
	string document;

	const bool result = ParseURL(url, protocol, port, host, document);

	REQUIRE(result);
	REQUIRE(protocol == Protocol::HTTPS);
	REQUIRE(port == 443);
	REQUIRE(host == "localhost");
	REQUIRE(document == "doc/");
}


TEST_CASE("correct port parsing test")
{
	const string url = "https://oop.com:8000/";

	Protocol protocol;
	unsigned port;
	string host;
	string document;

	const bool result = ParseURL(url, protocol, port, host, document);

	REQUIRE(result);
	REQUIRE(protocol == Protocol::HTTPS);
	REQUIRE(port == 8000);
	REQUIRE(host == "oop.com");
	REQUIRE(document == "");
}

TEST_CASE("document parsing test")
{
	const string url = "https://oop.com:8000/documentLevel1/documentLevel2/index.html";

	Protocol protocol;
	unsigned port;
	string host;
	string document;

	const bool result = ParseURL(url, protocol, port, host, document);

	REQUIRE(result);
	REQUIRE(protocol == Protocol::HTTPS);
	REQUIRE(port == 8000);
	REQUIRE(host == "oop.com");
	REQUIRE(document == "documentLevel1/documentLevel2/index.html");
}

TEST_CASE("incorrect port parsing test")
{
	const string urlPortOutOfRange = "https://oop.com:66000/";
	const string urlIncorrectPortChars = "https://oop.com:abcd/";

	Protocol protocol;
	unsigned port;
	string host;
	string document;

	const bool resultPortOutOfRange = ParseURL(urlPortOutOfRange, protocol, port, host, document);
	const bool resultIncorrectPortChars = ParseURL(urlIncorrectPortChars, protocol, port, host, document);

	REQUIRE(!resultPortOutOfRange);
	REQUIRE(!resultIncorrectPortChars);
}


TEST_CASE("incorrect url parsing test")
{
	const string url1 = "https://:8000/documentLevel1/documentLevel2/index.html";
	const string url2 = "https://.:8000/documentLevel1/documentLevel2/index.html";

	Protocol protocol;
	unsigned port;
	string host;
	string document;

	const bool result1 = ParseURL(url1, protocol, port, host, document);
	const bool result2 = ParseURL(url2, protocol, port, host, document);

	REQUIRE(!result1);
	REQUIRE(!result2);
}