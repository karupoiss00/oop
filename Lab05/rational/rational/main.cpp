#include <iostream>
#include "Rational.h"

using namespace std;

bool ReadRational(istream& input, CRational& rational);

int main()
{
	CRational first, second;

	cout << "Enter two rationals: " << endl;
	
	if (!ReadRational(cin, first) || !ReadRational(cin, second))
	{
		return 1;
	}

	cout << "sum = " << first + second << endl;
	cout << "(sum * 2 / 3) = " << (first + second) * 2 / 3 << endl;
	cout << "(sum * 2 / 3) + 5 = " << (first + second) * 2 / 3 + 5 << endl;
	cout << "ToDouble: " << (first + second).ToDouble() << endl;

	auto rat = first.ToCompoundFraction();

	cout << rat.first << " " << rat.second << endl;

	return 0;
}

bool ReadRational(istream& input, CRational& rational)
{
	try
	{
		input >> rational;
	}
	catch (std::exception const& e)
	{
		cout << e.what() << endl;
		return false;
	}

	return true;
}