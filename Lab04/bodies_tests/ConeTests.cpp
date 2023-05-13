#include <catch2/catch.hpp>
#define _USE_MATH_DEFINES
#include <math.h>	 
#include "../bodies/Cone.h"

struct Cone_
{
	const double expectedRadius = 42.8;
	const double expectedDensity = 8.8;
	const double expectedHeight = 10;
	const double expectedVolume = 19182.9836;
	const CCone cone;
	Cone_()
		: cone(expectedDensity, expectedRadius, expectedHeight)
	{}
};

TEST_CASE_METHOD(Cone_, "Cone")
{

	SECTION("is a body")
	{
		CHECK(static_cast<const CBody*>(&cone));
	}

	SECTION("has a radius")
	{
		CHECK(cone.GetRadius() == expectedRadius);
	}

	SECTION("has a height")
	{
		CHECK(cone.GetHeight() == expectedHeight);
	}

	SECTION("has a density")
	{
		CHECK(static_cast<const CBody&>(cone).GetDensity() == expectedDensity);
	}

	SECTION("has a volume")
	{
		CHECK(static_cast<const CBody&>(cone).GetVolume() == Approx(expectedVolume));
	}

	SECTION("has a mass")
	{
		CHECK(static_cast<const CBody&>(cone).GetMass() == Approx(expectedVolume * expectedDensity));
	}

	SECTION("can be converted to string")
	{
		const auto expectedString = R"(cone
  density = 8.8
  volume = 19182.98362
  mass = 168810.2559
  radius = 42.8
  height = 10
)";
		CHECK(static_cast<const CBody&>(cone).ToString() == expectedString);
	}
}