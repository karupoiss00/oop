#pragma once
#include <sstream>
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <optional>
#include "Calculator.h"

class CalculatorController
{
public:
	CalculatorController(Calculator& calculator, std::istream& input, std::ostream& output);

	bool HandleCommand();

private:
	void DefineVariable(std::string expression);
	void AssignVariable(std::string expression);
	void DefineFunction(std::string expression);
	void PrintIdentifierValue(std::string expression);
	void PrintVariables(std::string expression);
	void PrintFunctions(std::string expression);

	Operation MapCharToOperation(char ch) const;
	size_t GetOperationCharacterPos(std::string const& expression);
	void PrepareExpression(string& expression);

	using ActionMap = std::map<std::string, std::function<void(std::string expression)>>;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
	ActionMap m_actionMap;
};