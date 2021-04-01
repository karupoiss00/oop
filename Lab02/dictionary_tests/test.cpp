#include <iostream>
#include <catch2/catch.hpp>
#include "..\dictionary\Dictionary.h"

TEST_CASE("IsRussianLexem: check string")
{
	REQUIRE(IsLexemeRussian("������") == true);
	REQUIRE(IsLexemeRussian("apple") == false);
}