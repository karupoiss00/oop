#include "car.h"

using namespace std;

CCar::CCar()
	: m_isEngineOn(false), m_speed(0), m_gear(Gear::Neutral)
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

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::TurnOnEngine()
{
	if (m_isEngineOn)
	{
		return false;
	}
	else
	{
		m_isEngineOn = true;
		return true;
	}
}

bool CCar::TurnOffEngine()
{
	if (m_isEngineOn && (GetDirection() == Direction::Stop) && (m_gear == Gear::Neutral))
	{
		m_isEngineOn = false;
		return true;
	}

	return false;
}

bool CCar::SetGear(Gear gear)
{
	if ((gear < Gear::Reverse) || (gear > Gear::Fifth))
	{
		return false;
	}

	if ((!m_isEngineOn && gear != Gear::Neutral) || gear == m_gear)
	{
		return false;
	}

	if (GetDirection() == Direction::Backward)
	{
		return SetGearWhenDirectionIsBack(gear);
	}

	if (gear == Gear::Reverse)
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

	if (speed > GetSpeed() && m_gear == Gear::Neutral)
	{
		return false;
	}

	if (!SpeedInGearRange(speed, m_gear))
	{
		return false;
	}

	if (GetDirection() == Direction::Backward || GetGear() == Gear::Reverse)
	{
		m_speed = -speed;
	}
	else
	{
		m_speed = speed;
	}

	return true;
}

bool CCar::SetGearWhenDirectionIsBack(Gear gear)
{
	if (!m_isEngineOn || (gear == m_gear) || (GetDirection() != Direction::Backward))
	{
		return false;
	}

	if (gear == Gear::Neutral)
	{
		m_gear = Gear::Neutral;
		return true;
	}

	return false;
}

bool CCar::SetReverseGear()
{
	if ((GetDirection() == Direction::Stop) && (m_gear == Gear::Neutral || m_gear == Gear::First))
	{
		m_gear = Gear::Reverse;
		return true;
	}

	return false;
}

bool CCar::SpeedInGearRange(int speed, Gear gear) const
{
	const int speedRanges[][2] = { {0, 20}, {0, 150}, {0, 30}, {20, 50}, {30, 60}, {40, 90}, {50, 150} };

	int minSpeed = speedRanges[static_cast<int>(gear) + 1][0];
	int maxSpeed = speedRanges[static_cast<int>(gear) + 1][1];

	return (speed >= minSpeed) && (speed <= maxSpeed);
}