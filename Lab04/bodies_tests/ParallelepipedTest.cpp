#include <catch2/catch.hpp>
#define _USE_MATH_DEFINES
#include <math.h>	 
#include "../bodies/Parallelepiped.h"

struct Parallelepiped_
{
	const double expectedWidth = 42.8;
	const double expectedHeight = 10;
	const double expectedDepth = 5;
	const double expectedDensity = 8.8;
	const double expectedVolume = 2140;
	const CParallelepiped parallelepiped;
	Parallelepiped_()
		: parallelepiped(expectedDensity, expectedWidth, expectedHeight, expectedDepth)
	{}
};

TEST_CASE_METHOD(Parallelepiped_, "Parallelepiped")
{

	SECTION("is a body")
	{
		CHECK(static_cast<const CBody*>(&parallelepiped));
	}

	SECTION("has a width")
	{
		CHECK(parallelepiped.GetWidth() == expectedWidth);
	}

	SECTION("has a height")
	{
		CHECK(parallelepiped.GetHeight() == expectedHeight);
	}

	SECTION("has a depth")
	{
		CHECK(parallelepiped.GetDepth() == expectedDepth);
	}

	SECTION("has a density")
	{
		CHECK(static_cast<const CBody&>(parallelepiped).GetDensity() == expectedDensity);
	}

	SECTION("has a volume")
	{
		CHECK(static_cast<const CBody&>(parallelepiped).GetVolume() == Approx(expectedVolume));
	}

	SECTION("has a mass")
	{
		CHECK(static_cast<const CBody&>(parallelepiped).GetMass() == Approx(expectedVolume * expectedDensity));
	}

	SECTION("can be converted to string")
	{
		const auto expectedString = R"(parallelepiped
  density = 8.8
  volume = 2140
  mass = 18832
  width = 42.8
  height = 10
  depth = 5
)";
		CHECK(static_cast<const CBody&>(parallelepiped).ToString() == expectedString);
	}
}