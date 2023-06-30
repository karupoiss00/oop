#include <catch2/catch.hpp>
#include "../calculator/Calculator.h"

using namespace std;

void CheckVariablesList(Calculator const& calculator, map<string, float> const& expectedVariables)
{
	auto varList = calculator.GetVariablesList();
	
	REQUIRE(varList.size() == expectedVariables.size());

	for (unsigned i = 0; i < varList.size(); i++)
	{
		auto it = expectedVariables.find(varList[i]);
		REQUIRE(it != expectedVariables.end());
		float expectedValue = it->second;

		if (isnan(expectedValue))
		{
			REQUIRE(isnan(calculator.GetIdentifierValue(varList[i])));
		}
		else
		{
			REQUIRE(calculator.GetIdentifierValue(varList[i]) == Approx(expectedValue).epsilon(1e-2));
		}
	}
}

void CheckFunctionsList(Calculator const& calculator, map<string, float> const& expectedFunctions)
{
	auto varList = calculator.GetFunctionsList();

	REQUIRE(varList.size() == expectedFunctions.size());

	for (unsigned i = 0; i < varList.size(); i++)
	{
		auto it = expectedFunctions.find(varList[i]);
		REQUIRE(it != expectedFunctions.end());
		float expectedValue = it->second;

		if (isnan(expectedValue))
		{
			REQUIRE(isnan(calculator.GetIdentifierValue(varList[i])));
		}
		else
		{
			REQUIRE(calculator.GetIdentifierValue(varList[i]) == Approx(expectedValue).epsilon(1e-2));
		}
	}
}

void CheckVariableValue(Calculator const& calculator, string const& variableName, float expectedValue)
{
	REQUIRE(calculator.GetIdentifierValue(variableName) == Approx(expectedValue).epsilon(1e-2));
}

TEST_CASE("create calculator")
{
	Calculator calculator;

	REQUIRE(calculator.GetFunctionsList().empty());
	REQUIRE(calculator.GetVariablesList().empty());
}

const string FIRST_VARIABLE_NAME = "v_1";
const string SECOND_VARIABLE_NAME = "v_2";
const string THIRD_VARIABLE_NAME = "v_3";
const string FIRST_FN_NAME = "fn_1";
const string SECOND_FN_NAME = "fn_2";

TEST_CASE("defining variable")
{
	Calculator calculator;

	SECTION("defining variable with unique name")
	{
		calculator.DefineVariable(FIRST_VARIABLE_NAME);

		CheckVariablesList(calculator, { {FIRST_VARIABLE_NAME, NAN} });

		SECTION("defining second variable with unique name")
		{
			calculator.DefineVariable(SECOND_VARIABLE_NAME);

			CheckVariablesList(calculator, { {FIRST_VARIABLE_NAME, NAN}, {SECOND_VARIABLE_NAME, NAN} });
		}

		SECTION("defining variable with defined name")
		{
			REQUIRE_THROWS(calculator.DefineVariable(FIRST_VARIABLE_NAME));
		}
	}
}

TEST_CASE("assign variable")
{
	Calculator calculator;

	SECTION("by float value")
	{
		calculator.AssignVariable(FIRST_VARIABLE_NAME, 25.55f);
		CheckVariableValue(calculator, FIRST_VARIABLE_NAME, 25.55f);
	}

	calculator.AssignVariable(FIRST_VARIABLE_NAME, 25.55f);

	SECTION("by identifier value")
	{
		calculator.AssignVariable(SECOND_VARIABLE_NAME, FIRST_VARIABLE_NAME);
		CheckVariableValue(calculator, SECOND_VARIABLE_NAME, 25.55f);

		SECTION("check, that assigned by value")
		{
			calculator.AssignVariable(FIRST_VARIABLE_NAME, 0);
			CheckVariableValue(calculator, SECOND_VARIABLE_NAME, 25.55f);
		}
	}

	SECTION("by undefined identifier")
	{
		REQUIRE_THROWS(calculator.AssignVariable(SECOND_VARIABLE_NAME, THIRD_VARIABLE_NAME));
	}

	calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME);

	SECTION("with defined function name identifier")
	{
		REQUIRE_THROWS(calculator.AssignVariable(SECOND_VARIABLE_NAME, FIRST_FN_NAME));
	}
}

TEST_CASE("define function")
{
	Calculator calculator;

	calculator.AssignVariable(FIRST_VARIABLE_NAME, 20.f);

	SECTION("by defined identifier")
	{
		calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME);
		CheckFunctionsList(calculator, { {FIRST_FN_NAME, 20.f} });

		SECTION("check that defined by value")
		{
			calculator.AssignVariable(FIRST_VARIABLE_NAME, 0.f);
			CheckFunctionsList(calculator, { {FIRST_FN_NAME, 20.f} });
		}
	}

	SECTION("by undefined identifier")
	{
		REQUIRE_THROWS(calculator.DefineFunction(FIRST_FN_NAME, SECOND_VARIABLE_NAME));
	}

	calculator.AssignVariable(SECOND_VARIABLE_NAME, 5.f);

	SECTION("by plus expression")
	{
		calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME, SECOND_VARIABLE_NAME, Operation::PLUS);
		CheckFunctionsList(calculator, { {FIRST_FN_NAME, 25.f} });

		SECTION("check that expression saving ref")
		{
			calculator.AssignVariable(FIRST_VARIABLE_NAME, 5.f);
			CheckFunctionsList(calculator, { {FIRST_FN_NAME, 10.f} });
		}
	}

	SECTION("by minus expression")
	{
		calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME, SECOND_VARIABLE_NAME, Operation::MINUS);
		CheckFunctionsList(calculator, { {FIRST_FN_NAME, 15.f} });
	}

	SECTION("by multiply expression")
	{
		calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME, SECOND_VARIABLE_NAME, Operation::MUPTIPLY);
		CheckFunctionsList(calculator, { {FIRST_FN_NAME, 100.f} });
	}

	SECTION("by divide expression")
	{
		calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME, SECOND_VARIABLE_NAME, Operation::DIVIDE);
		CheckFunctionsList(calculator, { {FIRST_FN_NAME, 4.f} });
	}

	calculator.DefineVariable(THIRD_VARIABLE_NAME);

	SECTION("with NAN in expressiong")
	{
		calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME, THIRD_VARIABLE_NAME, Operation::PLUS);
		CheckFunctionsList(calculator, { {FIRST_FN_NAME, NAN} });
	}

	calculator.AssignVariable(THIRD_VARIABLE_NAME, 0.f);

	SECTION("with dividing zero in expressiong")
	{
		calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME, THIRD_VARIABLE_NAME, Operation::DIVIDE);
		CheckFunctionsList(calculator, { {FIRST_FN_NAME, NAN} });
	}

	calculator.DefineFunction(FIRST_FN_NAME, FIRST_VARIABLE_NAME, SECOND_VARIABLE_NAME, Operation::PLUS);

	SECTION("with nested fn")
	{
		calculator.DefineFunction(SECOND_FN_NAME, FIRST_FN_NAME, SECOND_VARIABLE_NAME, Operation::DIVIDE);

		CheckFunctionsList(calculator, { {FIRST_FN_NAME, 25.f}, {SECOND_FN_NAME, 5.f} });
	}
}
