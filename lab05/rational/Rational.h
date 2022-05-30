#pragma once
#include <iostream>
#include <map>

const unsigned DEFAULT_DENOMINATOR = 1;

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	unsigned GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational operator+() const;
	CRational operator-() const;
	bool operator!() const;

protected:
	void Normalize();

private:
	int m_numerator;
	unsigned m_denominator;
};

CRational operator+(CRational const& rational1, CRational const& rational2);
CRational operator-(CRational const& rational1, CRational const& rational2);
CRational operator*(CRational const& rational1, CRational const& rational2);
CRational operator/(CRational const& rational1, CRational const& rational2);
CRational& operator+=(CRational& rational1, CRational const& rational2);
CRational& operator-=(CRational& rational1, CRational const& rational2);
CRational& operator*=(CRational& rational1, CRational const& rational2);
CRational& operator/=(CRational& rational1, CRational const& rational2);
bool operator==(CRational const& rational1, CRational const& rational2);
bool operator!=(CRational const& rational1, CRational const& rational2);
bool operator>(CRational const& rational1, CRational const& rational2);
bool operator>=(CRational const& rational1, CRational const& rational2);
bool operator<(CRational const& rational1, CRational const& rational2);
bool operator<=(CRational const& rational1, CRational const& rational2);
std::ostream& operator<<(std::ostream& output, CRational const& rational);
std::istream& operator >> (std::istream& input, CRational& rational);