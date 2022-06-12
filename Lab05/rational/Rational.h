#pragma once
#include <iostream>
#include <map>

const int DEFAULT_DENOMINATOR = 1;

class CRational final
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

	std::pair<int, CRational> ToCompoundFraction() const;

	CRational operator+() const;
	CRational operator-() const;
	CRational& operator+=(CRational const& rhs);
	CRational& operator-=(CRational const& rhs);
	CRational& operator*=(CRational const& rhs);
	CRational& operator/=(CRational const& rhs);

	bool operator!() const;

private:
	int m_numerator;
	int m_denominator;

	void SetRational(int numerator, int denominator);
	void Normalize();
};

CRational operator+(CRational lhs, CRational const& rhs);
CRational operator-(CRational lhs, CRational const& rhs);
CRational operator*(CRational lhs, CRational const& rhs);
CRational operator/(CRational lhs, CRational const& rhs);
bool operator==(CRational const& lhs, CRational const& rhs);
bool operator!=(CRational const& lhs, CRational const& rhs);
bool operator>(CRational const& lhs, CRational const& rhs);
bool operator>=(CRational const& lhs, CRational const& rhs);
bool operator<(CRational const& lhs, CRational const& rhs);
bool operator<=(CRational const& lhs, CRational const& rhs);
std::ostream& operator<<(std::ostream& output, CRational const& rhs);
std::istream& operator>>(std::istream& input, CRational& rhs);