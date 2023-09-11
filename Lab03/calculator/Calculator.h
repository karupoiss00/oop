#pragma once
#include <string>
#include <vector>
#include <optional>
#include <cmath>
#include <map>
#include <functional>

enum class Operation
{
	PLUS,
	MINUS,
	MUPTIPLY,
	DIVIDE,
};

class Calculator
{
public:
	void DefineVariable(std::string const& variableName);
	void AssignVariable(std::string const& lhsVariableName, std::string const& rhsVariableName);
	void AssignVariable(std::string const& lhsVariableName, float value);
	void DefineFunction(std::string const& functionName, std::string const& rhsIdentifier);
	void DefineFunction(std::string const& functionName, std::string const& lhsIdentifier, std::string const& rhsIdentifier, Operation operation);

	float GetIdentifierValue(std::string const& identifier) const;
	std::vector<std::string> GetVariablesList() const;
	std::vector<std::string> GetFunctionsList() const;

private:
	bool IsFunction(std::string const& name) const;
	bool IsIdentifierDefined(std::string const& name) const;
	// статический метод должен быть
	bool IsValidIdentifier(std::string const& identifier) const;
	// нужно использовать атрибут noreturn
	[[noreturn]] void ThrowAlreadyDefinedIdentifier(std::string const& identifier) const;
	void ThrowUndefinedIdentifier(std::string const& identifier) const;
	void ThrowIdentifierIsFunction(std::string const& identifier) const;

	float DoOperation(std::string const& lhsIdentifier, std::string const& rhsIdentifier, Operation operation) const;

	std::map<std::string, float, std::less<std::string>> m_variables;
	std::map<std::string, std::function<float()>, std::less<std::string>> m_functions;
};