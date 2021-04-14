#pragma once
#include <iostream>

enum Direction : int
{
	Stop = 0,
	Forward,
	Backward
};

enum Gears : int
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
	int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool m_isEngineOn;
	int m_speed;
	int m_gear;

	bool SetReverseGear();
	bool SetGearWhenDirectionIsBack(int gear);
	bool SpeedInGearRange(int speed, int gear) const;
};