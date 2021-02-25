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

int RadixInMaxPower(unsigned radix, int maxExponent, bool isNegative, bool& wasError)
{
	wasError = false;
	double maxPowerValue = pow(static_cast<float>(radix), maxExponent);
	unsigned int maxValue = INT_MAX;

	bool highestNumberValueOfRadixBiggerThanMaxInt = maxPowerValue > maxValue;

	if (highestNumberValueOfRadixBiggerThanMaxInt)
	{
		wasError = true;
	}

	return static_cast<int>(maxPowerValue);
}


bool CanAccumulate(unsigned& result, unsigned digit, unsigned radixInMaxPow, bool isNegative)
{
	unsigned int maxValue = isNegative ? INT_MAX + 1: INT_MAX;
	bool overflowDuringMultiplication = digit > maxValue / radixInMaxPow;
	bool overflowDuringAddition = result > maxValue - digit * radixInMaxPow;

	if (overflowDuringMultiplication || overflowDuringAddition)
	{
		return false;
	}

	result += digit * radixInMaxPow;
	return true;
}