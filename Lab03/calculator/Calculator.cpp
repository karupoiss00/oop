#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <cassert>
#include "Calculator.h"

using namespace std;

bool Calculator::IsIdentifierDefined(string const& name) const
{
	return m_variables.find(name) != m_variables.cend()
		|| m_functions.find(name) != m_functions.cend();
}

bool Calculator::IsFunction(string const& name) const
{
	return m_functions.find(name) != m_functions.cend();
}

bool Calculator::IsValidIdentifier(string const& identifier) const
{
	if (identifier.empty())
	{
		return false;
	}

	if (isdigit(identifier[0]))
	{
		return false;
	}

	return std::find_if(
		identifier.begin(), 
		identifier.end(),
		[](char c) 
		{
			return !(std::isalpha(c) || isdigit(c) || c == '_'); 
		}
	) == identifier.end();
}

void Calculator::AssignVariable(string const& lhsVariableName, float value)
{
	if (!IsValidIdentifier(lhsVariableName))
	{
		throw invalid_argument(lhsVariableName + " contains not allowed chars");
	}

	if (IsFunction(lhsVariableName))
	{
		ThrowIdentifierIsFunction(lhsVariableName);
	}

	m_variables[lhsVariableName] = value;
}

void Calculator::AssignVariable(string const& lhsVariableName, string const& rhsVariableName)
{
	if (IsFunction(rhsVariableName))
	{
		ThrowIdentifierIsFunction(lhsVariableName);
	}
	
	AssignVariable(lhsVariableName, GetIdentifierValue(rhsVariableName));
}

void Calculator::DefineVariable(string const& variableName)
{
	if (IsIdentifierDefined(variableName))
	{
		ThrowAlreadyDefinedIdentifier(variableName);
	}

	AssignVariable(variableName, NAN);
}

void Calculator::DefineFunction(string const& functionName, string const& rhsIdentifier)
{
	if (IsIdentifierDefined(functionName) && !IsFunction(functionName))
	{
		ThrowAlreadyDefinedIdentifier(functionName);
	}

	float rhsValue = GetIdentifierValue(rhsIdentifier);

	m_functions[functionName] = [rhsValue]() { return rhsValue; };
 };

void Calculator::DefineFunction(string const& functionName, string const& lhsIdentifier, string const& rhsIdentifier, Operation operation)
{
	if (!IsIdentifierDefined(lhsIdentifier))
	{
		ThrowUndefinedIdentifier(lhsIdentifier);
	}

	if (!IsIdentifierDefined(rhsIdentifier))
	{
		ThrowUndefinedIdentifier(rhsIdentifier);
	}

	m_functions[functionName] = bind(&Calculator::DoOperation, this, lhsIdentifier, rhsIdentifier, operation);
};

float Calculator::DoOperation(string const& lhsIdentifier, string const& rhsIdentifier, Operation operation) const
{
	float lhsValue = GetIdentifierValue(lhsIdentifier);
	float rhsValue = GetIdentifierValue(rhsIdentifier);

	switch (operation)
	{
	case Operation::PLUS:
		return lhsValue + rhsValue;
	case Operation::MINUS:
		return lhsValue - rhsValue;
	case Operation::MUPTIPLY:
		return lhsValue * rhsValue;
	case Operation::DIVIDE:
		if (rhsValue == 0)
		{
			return NAN;
		}

		return lhsValue / rhsValue;
	default:
		assert(false);
	}
}

vector<string> Calculator::GetVariablesList() const
{
	vector<string> variables;

	transform(m_variables.cbegin(), m_variables.cend(), back_inserter(variables), [](auto const& p) { return p.first; });

	return variables;
}

vector<string> Calculator::GetFunctionsList() const
{
	vector<string> functions;

	transform(m_functions.cbegin(), m_functions.cend(), back_inserter(functions), [](auto const& p) { return p.first; });

	return functions;
}

float Calculator::GetIdentifierValue(string const& identifier) const
{
	if (!IsIdentifierDefined(identifier))
	{
		ThrowUndefinedIdentifier(identifier);
	}

	if (IsFunction(identifier))
	{
		auto fn = m_functions.find(identifier)->second;

		return fn();
	}

	return m_variables.find(identifier)->second;
}

void Calculator::ThrowAlreadyDefinedIdentifier(string const& identifier) const 
{
	throw invalid_argument(identifier + " is already defined");
};

void Calculator::ThrowUndefinedIdentifier(string const& identifier) const
{
	throw invalid_argument(identifier + " is undefined");
};

void Calculator::ThrowIdentifierIsFunction(std::string const& identifier) const
{
	throw invalid_argument(identifier + " is function");
};
