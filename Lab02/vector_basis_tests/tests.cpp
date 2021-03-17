#include <catch2/catch.hpp>
#include "vector_basis/VectorProcessor.h"

TEST_CASE("ParseFloatsToVector: Empty string in input")
{
	std::vector<float> v;
	std::istringstream input("");
	REQUIRE(ParseFloatsToVector(input, v) == false);
}

TEST_CASE("ParseFloatsToVector: Incorrect input without number")
{
	std::vector<float> v;
	std::istringstream input("test incorrect string");
	REQUIRE(ParseFloatsToVector(input, v) == false);
}

TEST_CASE("ParseFloatsToVector: Part of input contains numbers, but contain non-digit chars")
{
	std::vector<float> v;
	std::istringstream input("1,001 2 3 oops 4");
	REQUIRE(ParseFloatsToVector(input, v) == false);
}

TEST_CASE("AddThreeMinElements: Vector with count of numbers less than 3")
{
	std::vector<float> v = { 1.001f, 16.f };
	REQUIRE(AddThreeMinElements(v) == false);
}

TEST_CASE("AddThreeMinElements: Vector with 3 numbers")
{
	std::vector<float> v = { 1.001f, 2.002f, 3.003f };
	std::vector<float> vExpected = { 7.007f, 8.008f, 9.009f };
	REQUIRE(AddThreeMinElements(v) == true);
	CHECK_THAT(v, Catch::Approx(vExpected).epsilon(1.e-3f));
}

TEST_CASE("AddThreeMinElements: Vector with count of numbers more than 3")
{
	std::vector<float> v = { 1.001f, 2.002f, 3.003f, 4.5f };
	std::vector<float> vExpected = { 7.007f, 8.008f, 9.009f, 10.506f };
	CHECK(AddThreeMinElements(v) == true);
	CHECK_THAT(v, Catch::Approx(vExpected).epsilon(1.e-3f));
}

TEST_CASE("AddThreeMinElements: Vector with zeros")
{
	std::vector<float> v = { 0, 0, 0, 0 };
	std::vector<float> vExpected = { 0, 0, 0, 0 };
	REQUIRE(AddThreeMinElements(v) == true);
	CHECK_THAT(v, Catch::Approx(vExpected).epsilon(1.e-3f));
}

