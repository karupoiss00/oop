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

CRational operator+(CRational const& rational1, CRational const& rational2)
{
	CRational result;
	result += rational1;
	result += rational2;

	return result;
}

CRational operator-(CRational const& rational1, CRational const& rational2)
{
	return rational1 + (-rational2);
}

CRational operator*(CRational const& rational1, CRational const& rational2)
{
	int gcdNum1Den2 = gcd(rational1.GetNumerator(), rational2.GetDenominator());
	int gcdNum2Den1 = gcd(rational2.GetNumerator(), rational1.GetDenominator());
	int firstNumerator = rational1.GetNumerator() / gcdNum1Den2;
	int firstDenominator = rational1.GetDenominator() / gcdNum2Den1;
	int secondNumerator = rational2.GetNumerator() / gcdNum2Den1;
	int secondDenominator = rational2.GetDenominator() / gcdNum1Den2;
	int resultNumerator = firstNumerator * secondNumerator;
	int resultDenominator = firstDenominator * secondDenominator;

	if (resultNumerator == 0)
	{
		return CRational();
	}

	return CRational
	(
		resultNumerator,
		resultDenominator
	);
}

CRational operator/(CRational const& rational1, CRational const& rational2)
{
	if (!rational2)
	{
		throw invalid_argument("division by zero");
	}

	CRational invertedSecondRational
	(
		rational2.GetDenominator(),
		rational2.GetNumerator()
	);

	return rational1 * invertedSecondRational;
}

CRational& CRational::operator+=(CRational const& rational)
{
	int addendumNumerator = rational.GetNumerator();
	int addendumDenominator = rational.GetDenominator();

	if (this->m_numerator == 0)
	{
		this->SetRational(addendumNumerator, addendumDenominator);
		return *this;
	}

	if (addendumNumerator == 0)
	{
		return *this;
	}

	int resultDenomirator = this->m_denominator * addendumDenominator;
	int resultNumerator = (this->m_numerator * addendumDenominator)
		+ (addendumNumerator * this->m_denominator);

	if (resultNumerator == 0)
	{
		this->SetRational(0, 1);
		return *this;
	}

	this->SetRational(resultNumerator, resultDenomirator);
	this->Normalize();
	return *this;
}

CRational& operator-=(CRational& rational1, CRational const& rational2)
{
	rational1 = rational1 - rational2;

	return rational1;
}

CRational& operator*=(CRational& rational1, CRational const& rational2)
{
	rational1 = rational1 * rational2;

	return rational1;
}

CRational& operator/=(CRational& rational1, CRational const& rational2)
{
	rational1 = rational1 / rational2;

	return rational1;
}

bool operator==(CRational const& rational1, CRational const& rational2)
{
	return (rational1.GetNumerator() == rational2.GetNumerator())
		&& (rational1.GetDenominator() == rational2.GetDenominator());
}

bool operator!=(CRational const& rational1, CRational const& rational2)
{
	return (rational1.GetNumerator() != rational2.GetNumerator())
		|| (rational1.GetDenominator() != rational2.GetDenominator());
}

bool operator>(CRational const& rational1, CRational const& rational2)
{
	return rational1.ToDouble() > rational2.ToDouble();
}

bool operator>=(CRational const& rational1, CRational const& rational2)
{
	return rational1.ToDouble() >= rational2.ToDouble();
}

bool operator<(CRational const& rational1, CRational const& rational2)
{
	return rational1.ToDouble() < rational2.ToDouble();
}

bool operator<=(CRational const& rational1, CRational const& rational2)
{
	return rational1.ToDouble() <= rational2.ToDouble();
}

ostream& operator<<(ostream& output, CRational const& rational)
{
	output << rational.GetNumerator() << "/" << rational.GetDenominator();
	return output;
}

istream& operator>>(istream& input, CRational& rational)
{
	int numerator;
	int denumerator;
	char delimeter;

	input >> numerator >> delimeter >> denumerator;

	if (delimeter == '/')
	{
		rational = CRational(numerator, denumerator);
	}
	else
	{
		throw std::domain_error("failed to parse rational from input");
	}

	return input;
}