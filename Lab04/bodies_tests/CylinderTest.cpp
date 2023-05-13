#include <catch2/catch.hpp>
#define _USE_MATH_DEFINES
#include <math.h>	 
#include "../bodies/Cylinder.h"

struct Cylinder_
{
	const double expectedRadius = 42.8;
	const double expectedDensity = 8.8;
	const double expectedHeight = 10;
	const double expectedVolume = 57548.95;
	const CCylinder cylinder;
	Cylinder_()
		: cylinder(expectedDensity, expectedRadius, expectedHeight)
	{}
};

TEST_CASE_METHOD(Cylinder_, "Cylinder")
{

	SECTION("is a body")
	{
		CHECK(static_cast<const CBody*>(&cylinder));
	}

	SECTION("has a radius")
	{
		CHECK(cylinder.GetRadius() == expectedRadius);
	}

	SECTION("has a height")
	{
		CHECK(cylinder.GetHeight() == expectedHeight);
	}

	SECTION("has a density")
	{
		CHECK(static_cast<const CBody&>(cylinder).GetDensity() == expectedDensity);
	}

	SECTION("has a volume")
	{
		CHECK(static_cast<const CBody&>(cylinder).GetVolume() == Approx(expectedVolume));
	}

	SECTION("has a mass")
	{
		CHECK(static_cast<const CBody&>(cylinder).GetMass() == Approx(expectedVolume * expectedDensity));
	}

	SECTION("can be converted to string")
	{
		const auto expectedString = R"(cylinder
  density = 8.8
  volume = 57548.95087
  mass = 506430.7676
  radius = 42.8
  height = 10
)";
		CHECK(static_cast<const CBody&>(cylinder).ToString() == expectedString);
	}
}