#include "Car.h"
#include "CarController.h"

using namespace std;
using namespace std::placeholders;

CCarController::CCarController(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car), m_input(input), m_output(output)
{
	m_actionMap.emplace("Info", bind(&CCarController::Info, this, _1));
	m_actionMap.emplace("EngineOn", bind(&CCarController::EngineOn, this, _1));
	m_actionMap.emplace("EngineOff", bind(&CCarController::EngineOff, this, _1));
	m_actionMap.insert(make_pair("SetGear", bind(&CCarController::SetGear, this, _1)));
	m_actionMap.insert(make_pair("SetSpeed", bind(&CCarController::SetSpeed, this, _1)));
}

bool CCarController::HandleCommand()
{
	string commandLine;

	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CCarController::Info(std::istream& args)
{
	string info = "Engine is ";
	info += m_car.IsEngineOn() ? "on" : "off";

	auto direct = m_car.GetDirection();

	switch (direct)
	{
	case Direction::Stop:
		info += "\nCar stands still";
		break;
	case Direction::Forward:
		info += "\nCar moves forward";
		break;
	case Direction::Backward:
		info += "\nCar moves backward";
		break;
	}

	info += "\nSpeed " + to_string(static_cast<long long>(m_car.GetSpeed()));
	info += "\nGear " + to_string(static_cast<long long>(m_car.GetGear()));

	m_output << info;
	return true;
}

bool CCarController::EngineOn(std::istream& args)
{
	if (m_car.IsEngineOn())
	{
		m_output << "Engine is already turned on";
		return true;
	}

	string info = m_car.TurnOnEngine() ? "Engine has been successfully turned on"
		: "Unable to turn on engine";
	m_output << info;
	return true;
}

bool CCarController::EngineOff(std::istream& args)
{
	if (!m_car.IsEngineOn())
	{
		m_output << "Engine is already turned off";
		return true;
	}

	string info = m_car.TurnOffEngine() ? "Engine has been successfully turned off"
		: "Unable to turned off engine";
	m_output << info;
	return true;
}

bool CCarController::SetGear(std::istream& args)
{
	int gear;
	string arg, info;

	args >> arg;

	if (StrArgToNumber(arg, gear))
	{
		if (m_car.SetGear(static_cast<Gear>(gear)))
		{
			info = "Gear has been successfully set";
			info += "\nCurrent gear: " + to_string(static_cast<long long>(gear));
		}
		else
		{
			info = "Unable to set gear";
		}

		m_output << info;
	}

	return true;
}

bool CCarController::SetSpeed(std::istream& args)
{
	int speed;
	string arg, info;

	args >> arg;

	if (StrArgToNumber(arg, speed))
	{
		if (m_car.SetSpeed(speed))
		{
			info = "Speed has been successfully set";
			info += "\nCurrent speed: " + to_string(static_cast<long long>(speed));
		}
		else
		{
			info = "Unable to set speed";
		}

		m_output << info;
	}

	return true;
}

bool CCarController::StrArgToNumber(const string& arg, int& number)
{
	try
	{
		number = stoi(arg);
	}
	catch (...)
	{
		m_output << "Invalid argument!";
		return false;
	}

	return true;
}