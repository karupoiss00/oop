#include <math.h>
#include <numeric>
#include <stdexcept>
#include "Rational.h"

using namespace std;

CRational::CRational()
	: m_numerator(0), m_denominator(DEFAULT_DENOMINATOR) {}

CRational::CRational(int value)
	: m_numerator(value), m_denominator(DEFAULT_DENOMINATOR) {}

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw invalid_argument("denominator must be not zero");
	}

	bool isPositive = (numerator * denominator) > 0;

	m_numerator = isPositive ? abs(numerator) : -abs(numerator);
	m_denominator = abs(denominator);

	Normalize();
}

void CRational::Normalize()
{
	int greatestCommonDivisor = gcd(abs(m_numerator), m_denominator);

	m_numerator /= greatestCommonDivisor;
	m_denominator /= greatestCommonDivisor;
}

void CRational::SetRational(int numerator, int denominator)
{
	m_numerator = numerator;
	m_denominator = denominator;

	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return double(m_numerator) / double(m_denominator);
}

pair<int, CRational> CRational::ToCompoundFraction() const
{
	int whole = m_numerator / int(m_denominator);
	int remainder = m_numerator % int(m_denominator);
	CRational rational =
		remainder == 0
		? CRational()
		: CRational(remainder, m_denominator);

	return make_pair(whole, rational);
}

CRational CRational::operator+() const
{
	return *this;
}

CRational CRational::operator-() const
{
	if (m_numerator == 0)
	{
		return *this;
	}
	return CRational(-m_numerator, m_denominator);
}

bool CRational::operator!() const
{
	return m_numerator == 0;
}

CRational operator+(CRational lhs, CRational const& rhs)
{
	lhs += rhs;

	return lhs;
}

CRational operator-(CRational lhs, CRational const& rhs)
{
	lhs -= rhs;

	return lhs;
}

CRational operator*(CRational lhs, CRational const& rhs)
{
	lhs *= rhs;

	return lhs;
}

CRational operator/(CRational lhs, CRational const& rhs)
{
	lhs /= rhs;

	return lhs;
}

CRational& CRational::operator+=(CRational const& rhs)
{
	if (m_numerator == 0)
	{
		SetRational(rhs.m_numerator, rhs.m_denominator);
		return *this;
	}

	if (rhs.m_numerator == 0)
	{
		return *this;
	}

	if (m_denominator == rhs.m_denominator)
	{
		SetRational(m_numerator + rhs.m_numerator, m_denominator);
		return *this;
	}

	int commonDenominator = lcm(m_denominator, rhs.m_denominator);
	int firstFactor = commonDenominator / m_denominator;
	int secondFactor = commonDenominator / rhs.m_denominator;
	int resultNumerator = m_numerator * firstFactor + rhs.m_numerator * secondFactor;

	if (resultNumerator == 0)
	{
		SetRational(0, 1);
		return *this;
	}

	SetRational(resultNumerator, commonDenominator);

	return *this;
}

CRational& CRational::operator-=(CRational const& rhs)
{
	return *this += -rhs;
}

CRational& CRational::operator*=(CRational const& rhs)
{
	int gcdNum1Den2 = gcd(m_numerator, rhs.m_denominator);
	int gcdNum2Den1 = gcd(rhs.m_numerator, m_denominator);

	int firstNumerator = m_numerator / gcdNum1Den2;
	int firstDenominator = m_denominator / gcdNum2Den1;

	int secondNumerator = rhs.m_numerator / gcdNum2Den1;
	int secondDenominator = rhs.m_denominator / gcdNum1Den2;

	int resultNumerator = firstNumerator * secondNumerator;
	int resultDenominator = firstDenominator * secondDenominator;

	if (resultNumerator == 0)
	{
		SetRational(0, 1);

		return *this;
	}

	m_numerator = resultNumerator;
	m_denominator = resultDenominator;

	return *this;
}

CRational& CRational::operator/=(CRational const& rhs)
{
	if (!rhs)
	{
		throw invalid_argument("division by zero");
	}

	return *this *= { rhs.m_denominator, rhs.m_numerator };
}

bool operator==(CRational const& lhs, CRational const& rhs)
{
	return (lhs.GetNumerator() == rhs.GetNumerator())
		&& (lhs.GetDenominator() == rhs.GetDenominator());
}

bool operator!=(CRational const& lhs, CRational const& rhs)
{
	return (lhs.GetNumerator() != rhs.GetNumerator())
		|| (lhs.GetDenominator() != rhs.GetDenominator());
}

bool operator>(CRational const& lhs, CRational const& rhs)
{
	return lhs.ToDouble() > rhs.ToDouble();
}

bool operator>=(CRational const& lhs, CRational const& rhs)
{
	return lhs.ToDouble() >= rhs.ToDouble();
}

bool operator<(CRational const& lhs, CRational const& rhs)
{
	return lhs.ToDouble() < rhs.ToDouble();
}

bool operator<=(CRational const& lhs, CRational const& rhs)
{
	return lhs.ToDouble() <= rhs.ToDouble();
}

ostream& operator<<(ostream& output, CRational const& rhs)
{
	output << rhs.GetNumerator() << "/" << rhs.GetDenominator();
	return output;
}

istream& operator>>(istream& input, CRational& rhs)
{
	int numerator;
	int denumerator;
	char delimeter;

	input >> numerator >> delimeter >> denumerator;

	if (delimeter == '/')
	{
		rhs = CRational(numerator, denumerator);
	}
	else
	{
		cout << "failed to parse rational from input" << endl;
	}

	return input;
}