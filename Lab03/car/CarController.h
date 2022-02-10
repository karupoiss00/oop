#pragma once

#include <stdio.h>
#include <tchar.h>

#include <sstream>
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include "Car.h"

class CCarController
{
public:
	CCarController(CCar& car, std::istream& input, std::ostream& output);
	
	bool HandleCommand();

private:
	bool Info(std::istream& args);
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);

	bool StrArgToNumber(const std::string& arg, int& number);

	using ActionMap = std::map<std::string, std::function<bool(std::istream& args)>>;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	ActionMap m_actionMap;
};