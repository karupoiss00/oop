#include <math.h>
#include <stdexcept>
#include "Rational.h"

using namespace std;

CRational::CRational()
	: m_numerator(0), m_denominator(DEFAULT_DENOMINATOR) {}

CRational::CRational(int value)
	: m_numerator(value), m_denominator(DEFAULT_DENOMINATOR) {}

CRational::CRational(int numerator, int denominator)
{
	if (numerator == 0)
	{
		throw invalid_argument("numerator must be not zero");
	}
	if (denominator == 0)
	{
		throw invalid_argument("denominator must be not zero");
	} 

	bool isPositive = (numerator * denominator) > 0;
	
	m_numerator = isPositive ? abs(numerator) : -abs(numerator);
	m_denominator = abs(denominator);
	
	Normalize();
}

unsigned GreatestCommonDivisor(unsigned a, unsigned b)
{
	if (a < b)
	{
		swap(a, b); 
	}

	while (a % b != 0)
	{
		a = a % b;
		swap(a, b);
	}

	return b;
}

void CRational::Normalize()
{
	int greatestCommonDivisor = int(GreatestCommonDivisor(abs(m_numerator), m_denominator));
	
	m_numerator /= greatestCommonDivisor;
	m_denominator /= greatestCommonDivisor;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

unsigned CRational::GetDenominator() const
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
	int remainder = m_numerator % m_denominator;
	CRational rational =
		remainder == 0
		? CRational()
		: CRational(abs(remainder), m_denominator);

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
	int firstNumerator = rational1.GetNumerator();
	unsigned firstDenomitor = rational1.GetDenominator();
	int secondNumerator = rational2.GetNumerator();
	unsigned secondDenominator = rational2.GetDenominator();

	if (firstNumerator == 0)
	{
		return rational2;
	}

	if (secondNumerator == 0)
	{
		return rational1;
	}
	
	int commonDenomirator = firstDenomitor * secondDenominator;
	int resultNumerator = (firstNumerator * secondDenominator)
		+ (secondNumerator * firstDenomitor);

	if (resultNumerator == 0)
	{
		return CRational();
	}

	return CRational
	(
		resultNumerator,
		commonDenomirator
	);
}

CRational operator-(CRational const& rational1, CRational const& rational2)
{
	return rational1 + (-rational2);
}

CRational operator*(CRational const& rational1, CRational const& rational2)
{
	int firstNumerator = rational1.GetNumerator();
	unsigned firstDenomitor = rational1.GetDenominator();
	int secondNumerator = rational2.GetNumerator();
	unsigned secondDenominator = rational2.GetDenominator();

	int resultNumerator = firstNumerator * secondNumerator;

	if (resultNumerator == 0)
	{
		return CRational();
	}

	unsigned resultDenominator = firstDenomitor * secondDenominator;

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
		throw overflow_error("Divide by zero exception");
	}

	CRational rational2Inverted
	(
		rational2.GetDenominator(),
		rational2.GetNumerator()
	);

	return rational1 * rational2Inverted;
}

CRational& operator+=(CRational& rational1, CRational const& rational2)
{
	rational1 = rational1 + rational2;

	return rational1;
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