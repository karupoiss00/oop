#include "Translations.h"

using namespace std;

string ConvertNumber(const string& numberStr, unsigned fromRadix, unsigned toRadix)
{
	bool wasError = false;

	int value = StringToInt(numberStr, fromRadix, wasError);
	if (wasError)
	{
		cout << endl << GetErrorMessage(value) << endl;
		return "";
	}

	string errorMsg;
	string converted = IntToString(value, toRadix, errorMsg);
	if (!errorMsg.empty())
	{
		cout << endl << converted << endl;
		return "";
	}

	return converted;
}

int RadixInMaxPower(unsigned radix, unsigned maxExponent, bool isNegative, bool& wasError)
{
	wasError = false;
	int maxPowerValue = 1;
	int maxValue = isNegative ? INT_MIN : INT_MAX;
	bool highestNumberValueOfRadixBiggerThanMaxInt = false;

	for (size_t i = 0; i < maxExponent; i++)
	{
		if (maxValue / radix > maxPowerValue)
		{
			maxPowerValue *= radix;
		}
		else
		{
			highestNumberValueOfRadixBiggerThanMaxInt = true;
		}
	}

	if (highestNumberValueOfRadixBiggerThanMaxInt)
	{
		wasError = true;
	}

	return static_cast<int>(maxPowerValue);
}


bool CanAccumulate(unsigned& result, unsigned digit, unsigned radixInMaxPow, bool isNegative)
{
	int maxValue = isNegative ? INT_MIN : INT_MAX;

	bool overflowDuringMultiplication = digit > maxValue / radixInMaxPow;
	bool overflowDuringAddition = result > maxValue - digit * radixInMaxPow;

	if (overflowDuringMultiplication || overflowDuringAddition)
	{
		return false;
	}

	result += digit * radixInMaxPow;
	return true;
}