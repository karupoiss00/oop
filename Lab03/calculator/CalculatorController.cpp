#include <string>
#include <cassert>
#include "CalculatorController.h"

using namespace std;
using namespace std::placeholders;

CalculatorController::CalculatorController(Calculator& calculator, istream& input, ostream& output)
	: m_calculator(calculator), m_input(input), m_output(output)
{
	m_actionMap.emplace("var", bind(&CalculatorController::DefineVariable, this, _1));
	m_actionMap.emplace("let", bind(&CalculatorController::AssignVariable, this, _1));
	m_actionMap.emplace("fn", bind(&CalculatorController::DefineFunction, this, _1));
	m_actionMap.emplace("print", bind(&CalculatorController::PrintIdentifierValue, this, _1));
	m_actionMap.emplace("printvars", bind(&CalculatorController::PrintVariables, this, _1));
	m_actionMap.emplace("printfns", bind(&CalculatorController::PrintFunctions, this, _1));
}

Operation CalculatorController::MapCharToOperation(char ch) const
{
	switch (ch)
	{
	case '+':
		return Operation::PLUS;
	case '-':
		return Operation::MINUS;
	case '/':
		return Operation::DIVIDE;
	case '*':
		return Operation::MUPTIPLY;
	default:
		assert(false);
		throw;
	}
}

void PrepareExpression(string& expression)
{
	expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
}

bool CalculatorController::HandleCommand()
{
	string commandLine;

	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		string remainingStr;
		getline(strm, remainingStr);
		it->second(remainingStr);

		return true;
	}

	return false;
}

void CalculatorController::DefineVariable(string expression)
{
	stringstream input(expression);
	string variableName;
	input >> variableName;

	m_calculator.DefineVariable(variableName);
};

void CalculatorController::AssignVariable(string expression)
{
	PrepareExpression(expression);

	size_t equalCharPos = expression.find_first_of('=');

	if (equalCharPos == string::npos)
	{
		m_output << "incorrect syntax error" << endl;
		return;
	}

	string variableName = expression.substr(0, equalCharPos);
	string variableValue = expression.substr(equalCharPos + 1, expression.length() - equalCharPos);

	float numericValue = NAN;

	try
	{
		numericValue = stof(variableValue);
		m_calculator.AssignVariable(variableName, numericValue);
	}
	catch (std::exception const& e)
	{
		if (isnan(numericValue))
		{
			m_calculator.AssignVariable(variableName, variableValue);
		}
		else
		{
			m_output << e.what() << endl;
		}
	}
};

size_t CalculatorController::GetOperationCharacterPos(string const& expression)
{
	size_t operationCharPos = string::npos;
	
	size_t plusPos = expression.find_first_of('+');
	size_t minusPos = expression.find_first_of('-');
	size_t multiplyPos = expression.find_first_of('*');
	size_t dividerPos = expression.find_first_of('/');

	if (plusPos != string::npos)
	{
		operationCharPos = plusPos;
	}
	else if (minusPos != string::npos)
	{
		operationCharPos = minusPos;
	}
	else if (multiplyPos != string::npos)
	{
		operationCharPos = multiplyPos;
	}
	else if (dividerPos != string::npos)
	{
		operationCharPos = dividerPos;
	}

	if (operationCharPos == string::npos)
	{
		return string::npos;
	}

	return operationCharPos;
}

void CalculatorController::DefineFunction(string expression)
{
	PrepareExpression(expression);

	size_t equalCharPos = expression.find_first_of('=');
	size_t operationCharPos = GetOperationCharacterPos(expression);

	if (equalCharPos == string::npos || operationCharPos == string::npos)
	{
		m_output << "invalid syntax error" << endl;
		return;
	}

	string functionName = expression.substr(0, equalCharPos);
	string lhsArgument = expression.substr(equalCharPos + 1, operationCharPos - equalCharPos - 1);
	string rhsArgument = expression.substr(operationCharPos + 1, expression.length() - operationCharPos);
	Operation operation = MapCharToOperation(expression[operationCharPos]);

	m_calculator.DefineFunction(functionName, lhsArgument, rhsArgument, operation);
};

void CalculatorController::PrintIdentifierValue(string expression)
{
	string identifier;
	stringstream input(expression);
	input >> identifier;

	m_output << m_calculator.GetIdentifierValue(identifier) << endl;
};

void CalculatorController::PrintVariables(string expression)
{
	for (auto fnName : m_calculator.GetVariablesList())
	{
		m_output << fnName << ":" << m_calculator.GetIdentifierValue(fnName) << endl;
	}
};

void CalculatorController::PrintFunctions(string expression)
{
	for (auto fnName : m_calculator.GetFunctionsList())
	{
		m_output << fnName << ":" << m_calculator.GetIdentifierValue(fnName) << endl;
	}
};