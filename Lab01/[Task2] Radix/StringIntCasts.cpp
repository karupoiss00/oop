#include "StringIntCasts.h"

using namespace std;

unsigned PreporationToConverting(string& str, unsigned radix, unsigned& power, bool& isNegative)
{
	isNegative = false;

	if (!str.length())
	{
		return Errors::EMPTY_STRING;
	}

	if (radix < 2 || radix > 36)
	{
		return Errors::INVALID_RADIX;
	}

	transform(str.begin(), str.end(), str.begin(), ::toupper);

	isNegative = (str[0] == '-') ? true : false;

	str = isNegative ? str.substr(1, str.length() - 1) : str;
	str = !isNegative && str[0] == '+' ? str.substr(1, str.length() - 1) : str;

	if (str.length() > 1)
	{
		size_t firstNotNull = str.find_first_not_of('0');
		str = firstNotNull == string::npos ? str : str.substr(firstNotNull);
	}

	bool wasError;
	size_t exponent = str.length() - 1;
	power = RadixInMaxPower(radix, exponent, isNegative, wasError);

	if (wasError)
	{
		return Errors::VALUE_OVERFLOW;
	}

	return 0;
}


unsigned CharToInt(char ch, bool& wasError)
{
	ch = toupper(ch);

	wasError = (ch < '0') ||
		((ch > '9') && (ch < 'A')) ||
		(ch > 'Z') ? true : false;

	if (wasError)
	{
		return  Errors::INVALID_CHAR;
	}

	if (ch < ':')
	{
		return ch - '0';
	}
	else
	{
		return (ch + 10) - 'A';
	}
}

int StringToInt(string str, unsigned radix, bool& wasError)
{
	wasError = false;
	unsigned result;
	unsigned power;
	bool isNegative;

	if (result = PreporationToConverting(str, radix, power, isNegative))
	{
		wasError = true;
		return result;
	}

	for (char ch : str)
	{
		unsigned digit = CharToInt(ch, wasError);

		if (wasError || digit >= radix)
		{
			wasError = true;
			result = Errors::INVALID_CHAR; // Returns error code
			break;
		}

		if (!CanAccumulate(result, digit, power, isNegative))
		{
			wasError = true;
			result = Errors::VALUE_OVERFLOW;
			break;
		}

		power = power / radix;
	}

	if (wasError)
	{
		return result;
	}

	int signedResult = static_cast<int>(result);
	return isNegative ? -signedResult : signedResult;
}

char IntToChar(int number)
{
	if (number < 0 || number > 35)
	{
		return 0;
	}

	if (number < 10)
	{
		return static_cast<char>(number + '0');
	}

	return static_cast<char>((number - 10) + 'A');
}

string IntToString(int number, unsigned radix, string& errorMsg)
{
	errorMsg = "";
	string result;

	if (radix < 2 || radix > 36)
	{
		errorMsg = GetErrorMessage(Errors::INVALID_RADIX);
		return result;
	}

	unsigned uintNumber = number < 0 ? static_cast<unsigned>(-number) : static_cast<unsigned>(number);

	do
	{
		int digit = uintNumber % radix;
		uintNumber = uintNumber / radix;

		char ch = IntToChar(digit);

		if (!ch)
		{
			errorMsg = "Unable to convert number into character";
			return "";
		}

		result.insert(result.begin(), ch);

	} while (uintNumber > 0);

	if (number < 0)
	{
		result.insert(result.begin(), '-');
	}

	return result;
}