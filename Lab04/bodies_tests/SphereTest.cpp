#include <catch2/catch.hpp>
#define _USE_MATH_DEFINES
#include <math.h>	 
#include "../bodies/Sphere.h"

struct Sphere_
{
	const double expectedRadius = 42.8;
	const double expectedDensity = 8.8;
	const double expectedVolume = 328412.68;
	const CSphere sphere;
	Sphere_()
		: sphere(expectedDensity, expectedRadius)
	{}
};

TEST_CASE_METHOD(Sphere_, "Sphere")
{

	SECTION("is a body")
	{
		CHECK(static_cast<const CBody*>(&sphere));
	}

	SECTION("has a radius")
	{
		CHECK(sphere.GetRadius() == expectedRadius);
	}

	SECTION("has a density")
	{
		CHECK(static_cast<const CBody&>(sphere).GetDensity() == expectedDensity);
	}

	SECTION("has a volume")
	{
		CHECK(static_cast<const CBody&>(sphere).GetVolume() == Approx(expectedVolume));
	}

	SECTION("has a mass")
	{
		CHECK(static_cast<const CBody&>(sphere).GetMass() == Approx(expectedVolume * expectedDensity));
	}

	SECTION("can be converted to string")
	{
		const auto expectedString = R"(sphere
  density = 8.8
  volume = 328412.6796
  mass = 2890031.581
  radius = 42.8
)";
		CHECK(static_cast<const CBody&>(sphere).ToString() == expectedString);
	}
}