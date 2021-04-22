#include "../car/Car.h"
#include "../car/CarController.h"
#include <catch2/catch.hpp>

void ExpectOperationSuccess(CCar& car, const std::function<bool(CCar& car)>& op, int speed, Gear gear, Direction dir, bool isEngineOn)
{
	REQUIRE(op(car));

	CHECK(car.GetSpeed() == speed);
	CHECK(car.GetGear() == gear);
	CHECK(car.GetDirection() == dir);
	CHECK(car.IsEngineOn() == isEngineOn);
}

void ExpectOperationFailure(const CCar& car, const std::function<bool(CCar& car)>& op)
{
	auto clone(car);
	REQUIRE(!op(clone));

	CHECK(car.GetSpeed() == clone.GetSpeed());
	CHECK(car.GetGear() == clone.GetGear());
	CHECK(car.GetDirection() == clone.GetDirection());
	CHECK(car.IsEngineOn() == clone.IsEngineOn());
}

struct CarFixture
{
	CCar car;

	void ExpectCannotSetSpeed(int speed);
	void ExpectCanSetSpeed(int speed, Gear gear, Direction dir, bool isEngineOn);
	void ExpectCanHaveSpeedInRange(int minSpeed, int maxSpeed, Gear expGear, Direction expDir, bool expEngineOn);

	void ExpectCanSetGear(int speed, Gear gear, Direction dir, bool isEngineOn);
	void ExpectCannotSetGear(int speed, Gear gear);
};

void CarFixture::ExpectCannotSetSpeed(int speed)
{
	ExpectOperationFailure(car, [=](CCar& car) {
		return car.SetSpeed(speed);
	});
}

void CarFixture::ExpectCanSetSpeed(int speed, Gear gear, Direction dir, bool isEngineOn)
{
	ExpectOperationSuccess(car, [=](CCar& car) {
		return car.SetSpeed(speed);
	}, speed, gear, dir, isEngineOn);
}

void CarFixture::ExpectCanHaveSpeedInRange(int minSpeed, int maxSpeed, Gear gear, Direction dir, bool isEngineOn)
{
	ExpectCannotSetSpeed(minSpeed - 1);
	ExpectCanSetSpeed(maxSpeed, gear, dir, isEngineOn);
	ExpectCannotSetSpeed(maxSpeed + 1);
}

void CarFixture::ExpectCanSetGear(int speed, Gear gear, Direction dir, bool isEngineOn)
{
	car.SetSpeed(speed);

	ExpectOperationSuccess(car, [=](CCar& car) {
		return car.SetGear(gear);
	}, speed, gear, dir, isEngineOn);
}

void CarFixture::ExpectCannotSetGear(int speed, Gear gear)
{
	car.SetSpeed(speed);

	ExpectOperationFailure(car, [=](CCar& car) {
		return car.SetGear(gear);
	});
}

TEST_CASE_METHOD(CarFixture, "Check creation")
{

	SECTION("Must be turned off")
	{
		REQUIRE(!car.IsEngineOn());
	}

	SECTION("Must have neutral gear and zero speed")
	{
		CHECK(car.GetGear() == Gear::Neutral);
		CHECK(car.GetSpeed() == 0);
	}
	SECTION("Must have stop direction")
	{
		CHECK(car.GetDirection() == Direction::Stop);
	}
};

struct CarEngineOnFixture : CarFixture
{
	CarEngineOnFixture()
	{
		car.TurnOnEngine();
	}
};

SCENARIO("Backward movement")
{
	GIVEN("Car on reverse gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::Neutral);

		WHEN("sdsd")
		{
			THEN("lskdjslfk")
			{

			}
		}

		WHEN("")
		{

		}
	}
}


TEST_CASE_METHOD(CarEngineOnFixture, "Car after turning on")
{
	SECTION("Can be turned off")
	{
		CHECK(car.TurnOffEngine());
	}

	SECTION("Is in neutral")
	{
		CHECK(car.GetGear() == Gear::Neutral);
	}
	SECTION("Has zero speed")
	{
		CHECK(car.GetSpeed() == 0);
		CHECK(car.GetDirection() == Direction::Stop);
	}

	SECTION("Can be switched to reverse")
	{
		CHECK(car.SetGear(Gear::Reverse));
	}

	SECTION("Can be switched to first gear")
	{
		CHECK(car.SetGear(Gear::First));
	}
}

struct CarInReverseGearFixture : CarEngineOnFixture
{
	CarInReverseGearFixture()
	{
		car.SetGear(Gear::Reverse);
	}
};

TEST_CASE_METHOD(CarInReverseGearFixture, "Car after set reverse gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Can have speed from 0 to 20")
	{
		ExpectCanHaveSpeedInRange(0, 20, Gear::Reverse, Direction::Backward, true);
	}

	SECTION("Can be switch tofirst gear if have zero speed")
	{
		ExpectCannotSetGear(10, Gear::First);
		ExpectCanSetGear(0, Gear::First, Direction::Stop, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(20, Gear::Neutral, Direction::Backward, true);
	}

	SECTION("Cannot be switched to second gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::Second);
	}

	SECTION("Cannot be switched to third gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::Third);
	}

	SECTION("Cannot be switched to fourth gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::Fourth);
	}

	SECTION("Cannot be switched to fifth gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::Fifth);
	}
}

struct CarInFirstGearFixture : CarEngineOnFixture
{
	CarInFirstGearFixture()
	{
		car.SetGear(Gear::First);
	}
};

TEST_CASE_METHOD(CarInFirstGearFixture, "Car after set first gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 0 to 30")
	{
		ExpectCanHaveSpeedInRange(0, 30, Gear::First, Direction::Forward, true);
	}

	SECTION("Can be switched on second")
	{
		ExpectCannotSetGear(19, Gear::Second);
		ExpectCanSetGear(20, Gear::Second, Direction::Forward, true);
	}

	SECTION("Can be switched to third gear if speed is bigger or equal than 30")
	{
		ExpectCannotSetGear(29, Gear::Third);
		ExpectCanSetGear(30, Gear::Third, Direction::Forward, true);
	}

	SECTION("Cannot be switched to fourth gear")
	{
		ExpectCannotSetGear(30, Gear::Fourth);
	}

	SECTION("Cannot be switched to fifth gear")
	{
		ExpectCannotSetGear(30, Gear::Fifth);
	}

	SECTION("Can be switched to reverse gear if speed is zero")
	{
		ExpectCannotSetGear(1, Gear::Reverse);
		ExpectCanSetGear(0, Gear::Reverse, Direction::Stop, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(30, Gear::Neutral, Direction::Forward, true);
	}
}

struct CarInSecondGearFixture : CarInFirstGearFixture
{
	CarInSecondGearFixture()
	{
		car.SetSpeed(20);
		car.SetGear(Gear::Second);
	}
};

TEST_CASE_METHOD(CarInSecondGearFixture, "Car after set second gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 20 to 50")
	{
		ExpectCanHaveSpeedInRange(20, 50, Gear::Second, Direction::Forward, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(car.GetSpeed(), Gear::Neutral, Direction::Forward, true);
	}

	SECTION("Can be switched on first if speed is smaller or equal than 30")
	{
		ExpectCannotSetGear(31, Gear::First);
		ExpectCanSetGear(30, Gear::First, Direction::Forward, true);
	}

	SECTION("Can be switched to third gear if speed is bigger or equal than 30")
	{
		ExpectCannotSetGear(29, Gear::Third);
		ExpectCanSetGear(30, Gear::Third, Direction::Forward, true);
	}

	SECTION("Can be switched to fourth gear if speed is bigger or equal than 40")
	{
		ExpectCannotSetGear(39, Gear::Fourth);
		ExpectCanSetGear(40, Gear::Fourth, Direction::Forward, true);
	}

	SECTION("Can be switched to fifth gear if speed is bigger or equal than 50")
	{
		ExpectCannotSetGear(49, Gear::Fifth);
		ExpectCanSetGear(50, Gear::Fifth, Direction::Forward, true);
	}

	SECTION("Cannot switched to reverse gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::Reverse);
	}
}

struct CarInThirdGearFixture : CarInSecondGearFixture
{
	CarInThirdGearFixture()
	{
		car.SetSpeed(30);
		car.SetGear(Gear::Third);
	}
};

TEST_CASE_METHOD(CarInThirdGearFixture, "Car after set third gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 30 to 60")
	{
		ExpectCanHaveSpeedInRange(30, 60, Gear::Third, Direction::Forward, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(car.GetSpeed(), Gear::Neutral, Direction::Forward, true);
	}

	SECTION("Can be switched on first if speed is smaller or equal than 30")
	{
		ExpectCannotSetGear(31, Gear::First);
		ExpectCanSetGear(30, Gear::First, Direction::Forward, true);
	}

	SECTION("Can be switched to second gear if speed is smaller or equal than 50")
	{
		ExpectCannotSetGear(51, Gear::Second);
		ExpectCanSetGear(50, Gear::Second, Direction::Forward, true);
	}

	SECTION("Can be switched to fourth gear if speed is bigger or equal than 40")
	{
		ExpectCannotSetGear(39, Gear::Fourth);
		ExpectCanSetGear(40, Gear::Fourth, Direction::Forward, true);
	}

	SECTION("Can be switched to fifth gear if speed is bigger or equal than 50")
	{
		ExpectCannotSetGear(49, Gear::Fifth);
		ExpectCanSetGear(50, Gear::Fifth, Direction::Forward, true);
	}

	SECTION("Cannot switched to reverse gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::Reverse);
	}
}

struct CarInFourthGearFixture : CarInThirdGearFixture
{
	CarInFourthGearFixture()
	{
		car.SetSpeed(40);
		car.SetGear(Gear::Fourth);
	}
};

TEST_CASE_METHOD(CarInFourthGearFixture, "Car after set fourth gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 40 to 90")
	{
		ExpectCanHaveSpeedInRange(40, 90, Gear::Fourth, Direction::Forward, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(car.GetSpeed(), Gear::Neutral, Direction::Forward, true);
	}

	SECTION("Cannot switched to first gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::First);
	}

	SECTION("Can be switched to second gear if speed is smaller or equal than 50")
	{
		ExpectCannotSetGear(51, Gear::Second);
		ExpectCanSetGear(50, Gear::Second, Direction::Forward, true);
	}

	SECTION("Can be switched to third gear if speed is smaller or equal than 60")
	{
		ExpectCannotSetGear(61, Gear::Third);
		ExpectCanSetGear(60, Gear::Third, Direction::Forward, true);
	}

	SECTION("Can be switched to fifth gear if speed is bigger or equal than 50")
	{
		ExpectCannotSetGear(49, Gear::Fifth);
		ExpectCanSetGear(50, Gear::Fifth, Direction::Forward, true);
	}

	SECTION("Cannot switched to reverse gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::Reverse);
	}
}

struct CarInFifthGearFixture : CarInFourthGearFixture
{
	CarInFifthGearFixture()
	{
		car.SetSpeed(50);
		car.SetGear(Gear::Fifth);
	}
};

TEST_CASE_METHOD(CarInFifthGearFixture, "Car after set fifth gear")
{
	SECTION("Cannot be turned off")
	{
		CHECK(!car.TurnOffEngine());
	}

	SECTION("Speed can be in range from 50 to 150")
	{
		ExpectCanHaveSpeedInRange(50, 150, Gear::Fifth, Direction::Forward, true);
	}

	SECTION("Can be switched to neutral")
	{
		ExpectCanSetGear(car.GetSpeed(), Gear::Neutral, Direction::Forward, true);
	}

	SECTION("Cannot switched to first gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::First);
	}

	SECTION("Can be switched to second gear if speed is smaller or equal than 50")
	{
		ExpectCannotSetGear(51, Gear::Second);
		ExpectCanSetGear(50, Gear::Second, Direction::Forward, true);
	}

	SECTION("Can be switched to third gear if speed is smaller or equal than 60")
	{
		ExpectCannotSetGear(61, Gear::Third);
		ExpectCanSetGear(60, Gear::Third, Direction::Forward, true);
	}

	SECTION("Can be switched to fifth gear if speed is smaller or equal than 90")
	{
		ExpectCannotSetGear(91, Gear::Fourth);
		ExpectCanSetGear(90, Gear::Fourth, Direction::Forward, true);
	}

	SECTION("Cannot switched to reverse gear")
	{
		ExpectCannotSetGear(car.GetSpeed(), Gear::Reverse);
	}
}

TEST_CASE("Car turned on, neutral gear, cannot speed up")
{
	CCar car;
	car.TurnOnEngine();
	CHECK(!car.SetSpeed(1));
}

TEST_CASE("Move forward")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(Gear::First);
	CHECK(car.SetSpeed(2));
	CHECK(car.GetDirection() == Direction::Forward);
}

TEST_CASE("Move backward")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(Gear::Reverse);
	CHECK(car.SetSpeed(1));
	CHECK(car.GetDirection() == Direction::Backward);
}