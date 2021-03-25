#include <catch2/catch.hpp>
#include "../html_decode/HtmlDecode.h"

/*
using namespace std::literals;

TEST_CASE("DecodeEntity: all characters decoding test")
{
	REQUIRE(DecodeEntity("&amp;"sv).ch == '&');
	REQUIRE(DecodeEntity("&lt;"sv).ch == '<');
	REQUIRE(DecodeEntity("&gt;"sv).ch == '>');
	REQUIRE(DecodeEntity("&apos;"sv).ch == '\'');
	REQUIRE(DecodeEntity("&quot;"sv).ch == '"');
}*/

TEST_CASE("HtmlDecode: all characters decoding test with another chars")
{
	std::string_view input = "&lt;h1&gt;Pinky &amp; Brain&lt;/h1&gt;";
	std::string output = "<h1>Pinky & Brain</h1>";
	REQUIRE(HtmlDecode(input) == output);
}

TEST_CASE("HtmlDecode: boundary values")
{
	std::string_view input = "lt; &amp gt;";
	std::string output = "lt; &amp gt;";
	REQUIRE(HtmlDecode(input) == output);
}

TEST_CASE("HtmlDecode: empty string")
{
	std::string_view input = "";
	std::string output = "";
	REQUIRE(HtmlDecode(input) == output);
}