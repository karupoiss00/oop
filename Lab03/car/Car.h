#pragma once
#include <iostream>

enum class Direction : int
{
	Stop = 0,
	Forward,
	Backward
};

enum class Gear : int
{
	Reverse = -1,
	Neutral,
	First,
	Second,
	Third,
	Fourth,
	Fifth
};

class CCar
{
public:
	CCar();

	bool IsEngineOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(int speed);

private:
	bool m_isEngineOn;
	int m_speed;
	Gear m_gear;

	[[nodiscard]] bool SetReverseGear();
	[[nodiscard]] bool SetGearWhenDirectionIsBack(Gear gear);
	[[nodiscard]] bool SpeedInGearRange(int speed, Gear gear) const;
};