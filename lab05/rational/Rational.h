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
	CRational& operator+=(CRational const& rational);
	bool operator!() const;

private:
	int m_numerator;
	int m_denominator;
	void SetRational(int numerator, int denominator);
	void Normalize();
};

CRational operator+(CRational const& rational1, CRational const& rational2);
CRational operator-(CRational const& rational1, CRational const& rational2);
CRational operator*(CRational const& rational1, CRational const& rational2);
CRational operator/(CRational const& rational1, CRational const& rational2);
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
std::istream& operator>>(std::istream& input, CRational& rational);