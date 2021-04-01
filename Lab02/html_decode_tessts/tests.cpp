#include <iostream>
#include <catch2/catch.hpp>
#include <cmath>
#include <chrono>
#include "..\dictionary\Dictionary.h"

TEST_CASE("IsRussianLexem: check timings and count of primes")
{
	REQUIRE(IsLexemeRussian("€блоко") == true);
	REQUIRE(IsLexemeRussian("apple") == false);
}