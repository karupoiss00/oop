#include <catch2/catch.hpp>
#include "../rational/Rational.h"

struct ExpectedRationalState
{
	ExpectedRationalState(int numeratorValue, int denominatorValue)
		: numerator(numeratorValue), denominator(denominatorValue)
	{
		value = double(numeratorValue) / double(denominatorValue);
	}

	int numerator;
	unsigned denominator;
	double value;
};

void RationalExpectation(const CRational& recieved,const ExpectedRationalState& expected)
{
	REQUIRE(recieved.GetNumerator() == expected.numerator);
	REQUIRE(recieved.GetDenominator() == expected.denominator);
	REQUIRE(recieved.ToDouble() == Approx(expected.value).epsilon(1.e-3f));
}

SCENARIO("Rational creation")
{
	GIVEN("no args")
	{
		ExpectedRationalState expected(0, DEFAULT_DENOMINATOR);
		CRational rational;
		RationalExpectation(rational, expected);
	}

	GIVEN("only numerator")
	{
		WHEN("numerator is negative")
		{
			int numerator = -5;
			ExpectedRationalState expected(numerator, DEFAULT_DENOMINATOR);
			CRational rational(numerator);

			RationalExpectation(rational, expected);
		}
		WHEN("numerator is zero")
		{
			int numerator = 0;
			ExpectedRationalState expected(numerator, DEFAULT_DENOMINATOR);
			CRational rational(numerator);

			RationalExpectation(rational, expected);
		}
		WHEN("numerator is positive")
		{
			int numerator = 5;
			ExpectedRationalState expected(numerator, DEFAULT_DENOMINATOR);
			CRational rational(numerator);

			RationalExpectation(rational, expected);
		}
	}

	GIVEN("numerator and denominator")
	{
		WHEN("numerator is negative")
		{
			int numerator = -5;
			AND_WHEN("denominator is negative")
			{
				int denominator = -10;
				ExpectedRationalState expected(1, 2);
				CRational rational(numerator, denominator);

				RationalExpectation(rational, expected);
			}
			AND_WHEN("denominator is positive")
			{
				int denominator = 10;
				ExpectedRationalState expected(-1, 2);
				CRational rational(numerator, denominator);

				RationalExpectation(rational, expected);
			}
		}
		WHEN("numerator is positive")
		{
			int numerator = 5;
			AND_WHEN("denominator is negative")
			{
				int denominator = -10;
				ExpectedRationalState expected(-1, 2);
				CRational rational(numerator, denominator);

				RationalExpectation(rational, expected);
			}
			AND_WHEN("denominator is positive")
			{
				int denominator = 10;
				ExpectedRationalState expected(1, 2);
				CRational rational(numerator, denominator);

				RationalExpectation(rational, expected);
			}
		}
		WHEN("numerator is zero")
		{
			int numerator = 0;
			AND_WHEN("denominator is negative")
			{
				int denominator = -10;
				const auto initZeroRational = [&]()
				{
					CRational rational(numerator, denominator);
				};
				REQUIRE_THROWS(initZeroRational());
			}
		}
		WHEN("denominator is zero")
		{
			const auto initRationalWithZeroDenominator = [&]()
			{
				CRational rational(5, 0);
			};

			REQUIRE_THROWS(initRationalWithZeroDenominator());
		}
	}
};

void UnaryPlusRationalTest(CRational rational, int numExp, unsigned denExp)
{
	ExpectedRationalState expected(numExp, denExp);

	rational = +rational;

	RationalExpectation(rational, expected);
}

void UnaryPlusIntTest(int intValue, int numExp, unsigned denExp)
{
	CRational rational;
	ExpectedRationalState expected(numExp, denExp);

	rational = +intValue;

	RationalExpectation(rational, expected);
}

SCENARIO("Unary plus operator applying")
{
	WHEN("rational is zero")
	{
		UnaryPlusRationalTest(CRational(), 0, DEFAULT_DENOMINATOR);
	}

	WHEN("rational is negative")
	{
		UnaryPlusRationalTest(CRational(-5, 10), -1, 2);
	}

	WHEN("rational is positive")
	{
		UnaryPlusRationalTest(CRational(5, 10), 1, 2);
	}

	WHEN("int is zero")
	{
		UnaryPlusIntTest(0, 0, DEFAULT_DENOMINATOR);
	}

	WHEN("int is negative")
	{
		UnaryPlusIntTest(-2, -2, 1);
	}

	WHEN("int is positive")
	{
		UnaryPlusIntTest(5, 5, 1);
	}
}

void UnaryMinusRationalTest(CRational rational, int numExp, unsigned denExp)
{
	ExpectedRationalState expected(numExp, denExp);

	rational = -rational;

	RationalExpectation(rational, expected);
}

void UnaryMinusIntTest(int intValue, int numExp, unsigned denExp)
{
	CRational rational;
	ExpectedRationalState expected(numExp, denExp);

	rational = -intValue;

	RationalExpectation(rational, expected);
}

void ExclamationRationalTest(CRational rational, bool expectedResult)
{
	REQUIRE(!rational == expectedResult);
}

SCENARIO("! operator applying")
{
	WHEN("rational is zero")
	{
		ExclamationRationalTest(CRational(), true);
	}

	WHEN("rational is negative")
	{
		ExclamationRationalTest(CRational(-5, 10), false);
	}

	WHEN("rational is positive")
	{
		ExclamationRationalTest(CRational(5, 10), false);
	}
}

SCENARIO("Unary minus operator applying")
{
	WHEN("rational is zero")
	{
		UnaryMinusRationalTest(CRational(), 0, DEFAULT_DENOMINATOR);
	}

	WHEN("rational is negative")
	{
		UnaryMinusRationalTest(CRational(-5, 10), 1, 2);
	}

	WHEN("rational is positive")
	{
		UnaryMinusRationalTest(CRational(5, 10), -1, 2);
	}

	WHEN("int is zero")
	{
		UnaryMinusIntTest(0, 0, DEFAULT_DENOMINATOR);
	}

	WHEN("int is negative")
	{
		UnaryMinusIntTest(-2, 2, 1);
	}

	WHEN("int is positive")
	{
		UnaryMinusIntTest(5, -5, 1);
	}
}

void RationalPlusRationalTest(CRational first, CRational second, int numExp, unsigned denExp)
{
	CRational sum;
	ExpectedRationalState expectedSum(numExp, denExp);

	sum = first + second;

	RationalExpectation(sum, expectedSum);
}

void RationalPlusIntTest(CRational first, int second, int numExp, unsigned denExp)
{
	CRational sum;
	ExpectedRationalState expectedSum(numExp, denExp);

	sum = first + second;

	RationalExpectation(sum, expectedSum);
}

void IntPlusRationalTest(int first, CRational second, int numExp, unsigned denExp)
{
	CRational sum;
	ExpectedRationalState expectedSum(numExp, denExp);

	sum = first + second;

	RationalExpectation(sum, expectedSum);
}

void IntPlusIntTest(int first, int second, int numExp, unsigned denExp)
{
	CRational sum;
	ExpectedRationalState expectedSum(numExp, denExp);

	sum = first + second;

	RationalExpectation(sum, expectedSum);
}

SCENARIO("Binary plus operator applying")
{
	GIVEN("zero rational")
	{
		CRational firstRational;

		AND_GIVEN("zero rational")
		{
			RationalPlusRationalTest(firstRational, CRational(), 0, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive rational")
		{
			RationalPlusRationalTest(firstRational, CRational(5, 10), 1, 2);
		}

		AND_GIVEN("negative rational")
		{
			RationalPlusRationalTest(firstRational, CRational(-5, 10), -1, 2);
		}

		AND_GIVEN("zero int")
		{
			RationalPlusIntTest(firstRational, 0, 0, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive int")
		{
			RationalPlusIntTest(firstRational, 5, 5, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("negative int")
		{
			RationalPlusIntTest(firstRational, -5, -5, DEFAULT_DENOMINATOR);
		}
	}

	GIVEN("positive rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("zero rational")
		{
			RationalPlusRationalTest(firstRational, CRational(), 1, 2);
		}

		AND_GIVEN("positive rational")
		{
			RationalPlusRationalTest(firstRational, CRational(4, 10), 9, 10);
		}

		AND_GIVEN("negative rational")
		{
			WHEN("result < 0")
			{
				RationalPlusRationalTest(firstRational, CRational(-6, 10), -1, 10);
			}

			WHEN("result > 0")
			{
				RationalPlusRationalTest(firstRational, CRational(-3, 10), 1, 5);
			}

			WHEN("result = 0")
			{
				RationalPlusRationalTest(firstRational, CRational(-5, 10), 0, DEFAULT_DENOMINATOR);
			}
		}

		AND_GIVEN("zero int")
		{
			RationalPlusIntTest(firstRational, 0, 1, 2);
		}

		AND_GIVEN("positive int")
		{
			RationalPlusIntTest(firstRational, 5, 11, 2);
		}

		AND_GIVEN("negative int")
		{
			WHEN("result < 0")
			{
				RationalPlusIntTest(firstRational, -1, -1, 2);
			}

			WHEN("result > 0")
			{
				RationalPlusIntTest(firstRational, 1, 3, 2);
			}

			WHEN("result = 0")
			{
				RationalPlusIntTest(CRational(4, 2), -2, 0, DEFAULT_DENOMINATOR);
			}
		}
	}

	GIVEN("negative rational")
	{
		CRational firstRational(-1, 2);

		AND_GIVEN("zero rational")
		{
			RationalPlusRationalTest(firstRational, CRational(), -1, 2);
		}

		AND_GIVEN("positive rational")
		{
			WHEN("result < 0")
			{
				RationalPlusRationalTest(firstRational, CRational(-6, 10), -11, 10);
			}

			WHEN("result > 0")
			{
				RationalPlusRationalTest(firstRational, CRational(6, 10), 1, 10);
			}

			WHEN("result = 0")
			{
				RationalPlusRationalTest(firstRational, CRational(5, 10), 0, DEFAULT_DENOMINATOR);
			}
		}

		AND_GIVEN("negative rational")
		{
			RationalPlusRationalTest(firstRational, CRational(-4, 10), -9, 10);
		}

		AND_GIVEN("zero int")
		{
			RationalPlusIntTest(firstRational, 0, -1, 2);
		}

		AND_GIVEN("positive int")
		{
			WHEN("result < 0")
			{
				RationalPlusIntTest(firstRational, -1, -3, 2);
			}

			WHEN("result > 0")
			{
				RationalPlusIntTest(firstRational, 1, 1, 2);
			}

			WHEN("result = 0")
			{
				RationalPlusIntTest(CRational(-4, 2), 2, 0, DEFAULT_DENOMINATOR);
			}
		}

		AND_GIVEN("negative int")
		{
			RationalPlusIntTest(firstRational, -5, -11, 2);
		}
	}

	GIVEN("zero int")
	{
		int firstInt = 0;

		AND_GIVEN("zero rational")
		{
			IntPlusRationalTest(firstInt, CRational(), 0, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive rational")
		{
			IntPlusRationalTest(firstInt, CRational(5, 10), 1, 2);
		}

		AND_GIVEN("negative rational")
		{
			IntPlusRationalTest(firstInt, CRational(-2), -2, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("zero int")
		{
			IntPlusIntTest(firstInt, 0, 0, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive int")
		{
			IntPlusIntTest(firstInt, 5, 5, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("negative int")
		{
			IntPlusIntTest(firstInt, -3, -3, DEFAULT_DENOMINATOR);
		}
	}

	GIVEN("positive int")
	{
		int firstInt = 2;

		AND_GIVEN("zero rational")
		{
			IntPlusRationalTest(firstInt, CRational(), 2, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive rational")
		{
			IntPlusRationalTest(firstInt, CRational(5, 10), 5, 2);
		}

		AND_GIVEN("negative rational")
		{
			WHEN("result < 0")
			{
				IntPlusRationalTest(firstInt, CRational(-25, 10), -1, 2);
			}

			WHEN("result > 0")
			{
				IntPlusRationalTest(firstInt, CRational(6, 10), 13, 5);
			}

			WHEN("result = 0")
			{
				IntPlusRationalTest(firstInt, CRational(-2), 0, DEFAULT_DENOMINATOR);
			}
		}

		AND_GIVEN("zero int")
		{
			IntPlusIntTest(firstInt, 0, 2, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive int")
		{
			IntPlusIntTest(firstInt, 5, 7, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("negative int")
		{
			WHEN("result < 0")
			{
				IntPlusIntTest(firstInt, -3, -1, DEFAULT_DENOMINATOR);
			}

			WHEN("result > 0")
			{
				IntPlusIntTest(firstInt, 1, 3, DEFAULT_DENOMINATOR);
			}

			WHEN("result = 0")
			{
				IntPlusIntTest(firstInt, -2, 0, DEFAULT_DENOMINATOR);
			}
		}
	}

	GIVEN("negative int")
	{
		int firstInt = -2;

		AND_GIVEN("zero rational")
		{
			IntPlusRationalTest(firstInt, CRational(), -2, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive rational")
		{
			WHEN("result < 0")
			{
				IntPlusRationalTest(firstInt, CRational(1, 2), -3, 2);
			}

			WHEN("result > 0")
			{
				IntPlusRationalTest(firstInt, CRational(6, 2), 1, DEFAULT_DENOMINATOR);
			}

			WHEN("result = 0")
			{
				IntPlusRationalTest(firstInt, CRational(2), 0, DEFAULT_DENOMINATOR);
			}
		}

		AND_GIVEN("negative rational")
		{
			IntPlusRationalTest(firstInt, CRational(-5, 10), -5, 2);
			
		}

		AND_GIVEN("zero int")
		{
			IntPlusIntTest(firstInt, 0, -2, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive int")
		{
			WHEN("result < 0")
			{
				IntPlusIntTest(firstInt, 1, -1, DEFAULT_DENOMINATOR);
			}

			WHEN("result > 0")
			{
				IntPlusIntTest(firstInt, 3, 1, DEFAULT_DENOMINATOR);
			}

			WHEN("result = 0")
			{
				IntPlusIntTest(firstInt, 2, 0, DEFAULT_DENOMINATOR);
			}
		}

		AND_GIVEN("negative int")
		{
			IntPlusIntTest(firstInt, -5, -7, DEFAULT_DENOMINATOR);
		}
	}
}

void RationalMultiplyRationalTest(CRational first, CRational second, int numExp, unsigned denExp)
{
	CRational result;
	ExpectedRationalState expectedResult(numExp, denExp);

	result = first * second;

	RationalExpectation(result, expectedResult);
}

SCENARIO("multiply operator applying")
{
	GIVEN("zero rational")
	{
		CRational firstRational;

		AND_GIVEN("zero rational")
		{
			RationalMultiplyRationalTest(firstRational, CRational(), 0, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("positive rational")
		{
			RationalMultiplyRationalTest(firstRational, CRational(1, 2), 0, DEFAULT_DENOMINATOR);
		}

		AND_GIVEN("negative rational")
		{
			RationalMultiplyRationalTest(firstRational, CRational(-1, 2), 0, DEFAULT_DENOMINATOR);
		}
	}

	GIVEN("positive rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("positive rational")
		{
			RationalMultiplyRationalTest(firstRational, CRational(4, 10), 1, 5);
		}

		AND_GIVEN("negative rational")
		{
			RationalMultiplyRationalTest(firstRational, CRational(-10, 5), -1, DEFAULT_DENOMINATOR);
		}
	}

	GIVEN("negative rational")
	{
		CRational firstRational(-1, 2);

		AND_GIVEN("positive rational")
		{
			RationalMultiplyRationalTest(firstRational, CRational(4, 10), -1, 5);
		}

		AND_GIVEN("negative rational")
		{
			RationalMultiplyRationalTest(firstRational, CRational(-10, 5), 1, DEFAULT_DENOMINATOR);
		}
	}
}

void RationalDivisionRationalTest(CRational first, CRational second, int numExp = 0, unsigned denExp = DEFAULT_DENOMINATOR)
{
	CRational result;
	ExpectedRationalState expectedResult(numExp, denExp);
	auto Division = [](CRational _first, CRational _second) -> CRational
	{
		return _first / _second;
	};

	if (!second)
	{
		REQUIRE_THROWS(Division(first, second));
		
		return;
	}

	result = Division(first, second);

	RationalExpectation(result, expectedResult);
}

SCENARIO("division operator applying")
{
	GIVEN("zero rational")
	{
		CRational firstRational;

		AND_GIVEN("zero rational")
		{
			RationalDivisionRationalTest(firstRational, CRational());
		}

		AND_GIVEN("positive rational")
		{
			RationalDivisionRationalTest(firstRational, CRational(1, 2));
		}

		AND_GIVEN("negative rational")
		{
			RationalDivisionRationalTest(firstRational, CRational(-1, 2));
		}
	}

	GIVEN("positive rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("zero rational")
		{
			RationalDivisionRationalTest(firstRational, CRational());
		}
		AND_GIVEN("positive rational")
		{
			RationalDivisionRationalTest(firstRational, CRational(4, 10), 5, 4);
		}

		AND_GIVEN("negative rational")
		{
			RationalDivisionRationalTest(firstRational, CRational(-10, 5), -1, 4);
		}
	}

	GIVEN("negative rational")
	{
		CRational firstRational(-1, 2);

		AND_GIVEN("zero rational")
		{
			RationalDivisionRationalTest(firstRational, CRational());
		}
		AND_GIVEN("positive rational")
		{
			RationalDivisionRationalTest(firstRational, CRational(4, 10), -5, 4);
		}

		AND_GIVEN("negative rational")
		{
			RationalDivisionRationalTest(firstRational, CRational(-10, 5), 1, 4);
		}
	}
}

void EqualRationalsTest(CRational first, CRational second, bool expectedResult)
{
	bool result = first == second;
	REQUIRE(result == expectedResult);
}

SCENARIO("== operator applying")
{
	GIVEN("zero rational")
	{
		AND_GIVEN("zero rational")
		{
			EqualRationalsTest(CRational(), CRational(), true);
		}

		AND_GIVEN("positive rational")
		{
			EqualRationalsTest(CRational(), CRational(1, 2), false);
		}

		AND_GIVEN("negative rational")
		{
			EqualRationalsTest(CRational(), CRational(-1, 2), false);
		}
	}

	GIVEN("positive rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("positive full equal rational")
		{
			EqualRationalsTest(firstRational, CRational(1, 2), true);
		}

		AND_GIVEN("positive equal rational")
		{
			EqualRationalsTest(firstRational, CRational(45, 90), true);
		}

		AND_GIVEN("abs equal negative rational")
		{
			EqualRationalsTest(firstRational, CRational(-36, 72), false);
		}

		AND_GIVEN("not equal positive rational")
		{
			EqualRationalsTest(firstRational, CRational(-35, 72), false);
		}
	}
}

void NotEqualRationalsTest(CRational first, CRational second, bool expectedResult)
{
	bool result = first != second;
	REQUIRE(result == expectedResult);
}

SCENARIO("!= operator applying")
{
	GIVEN("zero rational")
	{
		AND_GIVEN("zero rational")
		{
			NotEqualRationalsTest(CRational(), CRational(), false);
		}

		AND_GIVEN("positive rational")
		{
			NotEqualRationalsTest(CRational(), CRational(1, 2), true);
		}

		AND_GIVEN("negative rational")
		{
			NotEqualRationalsTest(CRational(), CRational(-1, 2), true);
		}
	}

	GIVEN("positive rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("positive full equal rational")
		{
			NotEqualRationalsTest(firstRational, CRational(1, 2), false);
		}

		AND_GIVEN("positive equal rational")
		{
			NotEqualRationalsTest(firstRational, CRational(45, 90), false);
		}

		AND_GIVEN("abs equal negative rational")
		{
			NotEqualRationalsTest(firstRational, CRational(-36, 72), true);
		}

		AND_GIVEN("not equal positive rational")
		{
			NotEqualRationalsTest(firstRational, CRational(-35, 72), true);
		}
	}
}

void BiggerRationalTest(CRational first, CRational second, bool expectedResult)
{
	bool result = first > second;
	REQUIRE(result == expectedResult);
}

SCENARIO("> operator applying")
{
	GIVEN("zero rational")
	{
		AND_GIVEN("zero rational")
		{
			BiggerRationalTest(CRational(), CRational(), false);
		}

		AND_GIVEN("positive rational")
		{
			BiggerRationalTest(CRational(), CRational(1, 2), false);
		}

		AND_GIVEN("negative rational")
		{
			BiggerRationalTest(CRational(), CRational(-1, 2), true);
		}
	}

	GIVEN("rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("equal rational")
		{
			BiggerRationalTest(firstRational, CRational(1, 2), false);
		}

		AND_GIVEN("bigger rational")
		{
			BiggerRationalTest(firstRational, CRational(46, 90), false);
		}

		AND_GIVEN("smaller rational")
		{
			BiggerRationalTest(firstRational, CRational(44, 90), true);
		}
	}
}

void BiggerOrEqualRationalTest(CRational first, CRational second, bool expectedResult)
{
	bool result = first >= second;
	REQUIRE(result == expectedResult);
}

SCENARIO(">= operator applying")
{
	GIVEN("zero rational")
	{
		AND_GIVEN("zero rational")
		{
			BiggerOrEqualRationalTest(CRational(), CRational(), true);
		}

		AND_GIVEN("positive rational")
		{
			BiggerOrEqualRationalTest(CRational(), CRational(1, 2), false);
		}

		AND_GIVEN("negative rational")
		{
			BiggerOrEqualRationalTest(CRational(), CRational(-1, 2), true);
		}
	}

	GIVEN("rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("equal rational")
		{
			BiggerOrEqualRationalTest(firstRational, CRational(212, 424), true);
			BiggerOrEqualRationalTest(firstRational, CRational(-2, -4), true);
		}

		AND_GIVEN("bigger rational")
		{
			BiggerOrEqualRationalTest(firstRational, CRational(46, 90), false);
		}

		AND_GIVEN("smaller rational")
		{
			BiggerOrEqualRationalTest(firstRational, CRational(44, 90), true);
		}
	}
}

void SmallerRationalTest(CRational first, CRational second, bool expectedResult)
{
	bool result = first < second;
	REQUIRE(result == expectedResult);
}

SCENARIO("< operator applying")
{
	GIVEN("zero rational")
	{
		AND_GIVEN("zero rational")
		{
			SmallerRationalTest(CRational(), CRational(), false);
		}

		AND_GIVEN("positive rational")
		{
			SmallerRationalTest(CRational(), CRational(1, 2), true);
		}

		AND_GIVEN("negative rational")
		{
			SmallerRationalTest(CRational(), CRational(-1, 2), false);
		}
	}

	GIVEN("rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("equal rational")
		{
			SmallerRationalTest(firstRational, CRational(1, 2), false);
		}

		AND_GIVEN("bigger rational")
		{
			SmallerRationalTest(firstRational, CRational(46, 90), true);
		}

		AND_GIVEN("smaller rational")
		{
			SmallerRationalTest(firstRational, CRational(44, 90), false);
		}
	}
}

void SmallerOrEqualRationalTest(CRational first, CRational second, bool expectedResult)
{
	bool result = first <= second;
	REQUIRE(result == expectedResult);
}

SCENARIO("<= operator applying")
{
	GIVEN("zero rational")
	{
		AND_GIVEN("zero rational")
		{
			SmallerOrEqualRationalTest(CRational(), CRational(), true);
		}

		AND_GIVEN("positive rational")
		{
			SmallerOrEqualRationalTest(CRational(), CRational(1, 2), true);
		}

		AND_GIVEN("negative rational")
		{
			SmallerOrEqualRationalTest(CRational(), CRational(-1, 2), false);
		}
	}

	GIVEN("rational")
	{
		CRational firstRational(1, 2);

		AND_GIVEN("equal rational")
		{
			SmallerOrEqualRationalTest(firstRational, CRational(212, 424), true);
			SmallerOrEqualRationalTest(firstRational, CRational(-2, -4), true);
		}

		AND_GIVEN("bigger rational")
		{
			SmallerOrEqualRationalTest(firstRational, CRational(46, 90), true);
		}

		AND_GIVEN("smaller rational")
		{
			SmallerOrEqualRationalTest(firstRational, CRational(44, 90), false);
		}
	}
}