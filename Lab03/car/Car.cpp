#include "car.h"

using namespace std;

CCar::CCar()
	: m_isEngineOn(false), m_speed(0), m_gear(Gears::Neutral)
{

}

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
}

Direction CCar::GetDirection() const
{
	if (!m_speed)
	{
		return Direction::Stop;
	}

	return (m_speed > 0) ? Direction::Forward : Direction::Backward;
}

int CCar::GetSpeed() const
{
	return abs(m_speed);
}

int CCar::GetGear() const
{
	return m_gear;
}

bool CCar::TurnOnEngine()
{
	return m_isEngineOn ? false : (m_isEngineOn = true);
}

bool CCar::TurnOffEngine()
{
	if (m_isEngineOn && (GetDirection() == Direction::Stop) && (m_gear == Gears::Neutral))
	{
		m_isEngineOn = false;
		return true;
	}

	return false;
}

bool CCar::SetGear(int gear)
{
	if ((gear < Gears::Reverse) || (gear > Gears::Fifth))
	{
		return false;
	}

	if ((!m_isEngineOn && gear != Gears::Neutral) || gear == m_gear)
	{
		return false;
	}

	if (GetDirection() == Direction::Backward)
	{
		return SetGearWhenDirectionIsBack(gear);
	}

	if (gear == Gears::Reverse)
	{
		return SetReverseGear();
	}

	if (SpeedInGearRange(GetSpeed(), gear))
	{
		m_gear = gear;
		return true;
	}

	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!IsEngineOn() || speed == GetSpeed() || speed < 0)
	{
		return false;
	}

	if (speed > GetSpeed() && m_gear == Gears::Neutral)
	{
		return false;
	}

	if (!SpeedInGearRange(speed, m_gear))
	{
		return false;
	}

	if (GetDirection() == Direction::Backward || GetGear() == Gears::Reverse)
	{
		m_speed = -speed;
	}
	else
	{
		m_speed = speed;
	}

	return true;
}

bool CCar::SetGearWhenDirectionIsBack(int gear)
{
	if (!m_isEngineOn || (gear == m_gear) || (GetDirection() != Direction::Backward))
	{
		return false;
	}

	if (gear == Gears::Neutral)
	{
		m_gear = Gears::Neutral;
		return true;
	}

	return false;
}

bool CCar::SetReverseGear()
{
	if ((GetDirection() == Direction::Stop) && (m_gear == Gears::Neutral || m_gear == Gears::First))
	{
		m_gear = Gears::Reverse;
		return true;
	}

	return false;
}

bool CCar::SpeedInGearRange(int speed, int gear) const
{
	const int speedRanges[][2] = { {0, 20}, {0, 150}, {0, 30}, {20, 50}, {30, 60}, {40, 90}, {50, 150} };

	int minSpeed = speedRanges[gear + 1][0];
	int maxSpeed = speedRanges[gear + 1][1];

	return (speed >= minSpeed) && (speed <= maxSpeed);
}