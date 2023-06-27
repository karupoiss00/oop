#include <sstream>
#include <catch2/catch.hpp>
#include "../string/String.h"

using namespace std;

#define REQUIRE_STR_EQUALITY(actual, expected) REQUIRE(strcmp(actual, expected) == 0)

TEST_CASE("creation")
{
	SECTION("default")
	{
		CString str;

		REQUIRE(!str.GetLength());
		REQUIRE_STR_EQUALITY(str.GetStringData(), "");
	}

	SECTION("from array of characters")
	{
		char chars[6] = "12345";
		CString str(chars);

		REQUIRE(str.GetLength() == 5);
		REQUIRE_STR_EQUALITY(str.GetStringData(), "12345");
	}

	SECTION("from part of array of characters")
	{
		char chars[11] = "1234567890";
		size_t length = 5;

		CString str(chars, length);

		REQUIRE(str.GetLength() == length);
		REQUIRE_STR_EQUALITY(str.GetStringData(), "12345");
	}

	SECTION("from copy string")
	{
		CString source("12345");
		CString str(source);

		REQUIRE(str.GetLength() == source.GetLength());
		REQUIRE_STR_EQUALITY(str.GetStringData(), source.GetStringData());

	}

	SECTION("from move string")
	{
		CString source("12345");
		size_t length = source.GetLength();
		CString str(move(source));

		REQUIRE(str.GetLength() == length);
		REQUIRE_STR_EQUALITY(str.GetStringData(), "12345");
		REQUIRE(source.GetLength() == 0);
		REQUIRE_STR_EQUALITY(source.GetStringData(), "");
	}

	SECTION("from stl string")
	{
		string source("12345");
		CString str(source);

		REQUIRE(str.GetLength() == source.size());
		REQUIRE_STR_EQUALITY(str.GetStringData(), source.c_str());
	}
}

TEST_CASE("operators overloaded")
{
	SECTION("assignment")
	{
		SECTION("copy value of other string")
		{
			CString str, other("12345");
			size_t length = other.GetLength();
			str = other;

			REQUIRE(str.GetLength() == length);
			REQUIRE_STR_EQUALITY(str.GetStringData(), other.GetStringData());
		}

		SECTION("move value of other string")
		{
			CString str = move(CString("ABCDE"));

			REQUIRE(str.GetLength() == 5);
			REQUIRE_STR_EQUALITY(str.GetStringData(), "ABCDE");
		}

		SECTION("self assignment working")
		{
			CString str("ABCDE");
			size_t length = str.GetLength();

			str = str;

			REQUIRE(str.GetLength() == length);
			REQUIRE_STR_EQUALITY(str.GetStringData(), "ABCDE");

			str = move(str);

			REQUIRE(str.GetLength() == length);
			REQUIRE_STR_EQUALITY(str.GetStringData(), "ABCDE");
		}
	}

	SECTION("addition")
	{
		SECTION("can concat two strings")
		{
			CString str1("12345");
			CString str2("67890");
			CString str3;

			CString str = str1 + str2;
			size_t length = str1.GetLength() + str2.GetLength();

			REQUIRE(str.GetLength() == length);
			REQUIRE_STR_EQUALITY(str.GetStringData(), "1234567890");

			str = str1 + str3;
			REQUIRE(str.GetLength() == str1.GetLength());
			REQUIRE_STR_EQUALITY(str.GetStringData(), str1.GetStringData());
		}

		SECTION("can concat string and c-string")
		{
			CString str1("12345");
			char str2[6] = "67890";

			CString str = str1 + str2;

			REQUIRE(str.GetLength() == 10);
			REQUIRE_STR_EQUALITY(str.GetStringData(), "1234567890");

			str = str2 + str1;

			REQUIRE(str.GetLength() == 10);
			REQUIRE_STR_EQUALITY(str.GetStringData(), "6789012345");
		}

		SECTION("can concat string and stl string")
		{
			CString str1("12345");
			string str2("67890");

			CString str = str1 + str2;

			REQUIRE(str.GetLength() == 10);
			REQUIRE_STR_EQUALITY(str.GetStringData(), "1234567890");

			str = str2 + str1;

			REQUIRE(str.GetLength() == 10);
			REQUIRE_STR_EQUALITY(str.GetStringData(), "6789012345");
		}
	}

	SECTION("addition assignment")
	{
		CString str1("12345");
		CString str2("67890");
		size_t length = str1.GetLength() + str2.GetLength();
		str1 += str2;

		REQUIRE(str1.GetLength() == length);
		REQUIRE_STR_EQUALITY(str1.GetStringData(), "1234567890");
	}

	SECTION("equal to")
	{
		CString str1("12345");
		CString str2("12345");
		CString str3("67890s");

		REQUIRE(str1 == str2);
		REQUIRE(!(str1 == str3));
	}

	SECTION("not equal to")
	{
		CString str1("12345");
		CString str2("12345");
		CString str3("67890s");

		REQUIRE(str1 != str3);
		REQUIRE(!(str1 != str2));
	}

	SECTION("comparision")
	{
		SECTION("less than")
		{
			CString str1("12345");
			CString str2("67890");

			REQUIRE(str1 < str2);
			REQUIRE(!(str2 < str1));
		}

		SECTION("substr less than")
		{
			CString str1("12345");
			CString str2("123456");

			REQUIRE(str1 < str2);
		}

		SECTION("less than or equal to")
		{
			CString str1("12345");
			CString str2("67890");
			CString str3("67890");

			REQUIRE(str1 <= str2);
			REQUIRE(str2 <= str3);
			REQUIRE(!(str2 <= str1));
		}

		SECTION("greater than")
		{
			CString str1("12345");
			CString str2("67890");

			REQUIRE(str2 > str1);
			REQUIRE(!(str1 >  str2));
		}

		SECTION("greater than substr")
		{
			CString str1("12345");
			CString str2("123456");

			REQUIRE(str2 > str1);
		}

		SECTION("greater than or equal to")
		{
			CString str1("12345");
			CString str2("67890");
			CString str3("67890");

			REQUIRE(str2 >= str1);
			REQUIRE(str3 >= str2);
			REQUIRE(!(str1 >= str2));
		}
	}

	SECTION("left shift")
	{
		CString str("12345");
		stringstream strm;

		strm << str << endl;

		string outputStr;
		getline(strm, outputStr);

		REQUIRE(outputStr == "12345");
	}

	SECTION("right shift")
	{
		CString str;
		stringstream strm("12345");

		strm >> str;

		REQUIRE_STR_EQUALITY(str.GetStringData(), "12345");
	}
}

TEST_CASE("return correct length")
{
	CString str("12345");
	REQUIRE(str.GetLength() == 5);
}


TEST_CASE("returns correct substring")
{
	CString str("12345");

	REQUIRE(str.SubString(1, 2) == "23");
	REQUIRE(str.SubString(1) == "2345");
	REQUIRE(str.SubString(6) == "");
}

TEST_CASE("remove all chars")
{
	CString str("12345");
	str.Clear();

	REQUIRE(str.GetLength() == 0);
	REQUIRE_STR_EQUALITY(str.GetStringData(), "");
}