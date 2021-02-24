#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <algorithm>
#include "Errors.h"

using namespace std;

struct Args
{
	string sourceNotation;
	string destinationNotation;
	string value;
};

optional<Args> ParseArgs(int argc, char* argv[]);
string ConvertNumber(const string& numberStr, unsigned fromRadix, unsigned toRadix);
int StringToInt(string str, unsigned radix, bool& wasError);
string IntToString(int number, unsigned radix, string& errorMsg);
unsigned PreporationToConverting(string& str, unsigned radix, unsigned& power, bool& isNegative);
int RadixInMaxPower(unsigned radix, int maxExponent, bool isNegative, bool& wasError);
char IntToChar(int number);
unsigned CharToInt(char ch, bool& wasError);
bool CanAccumulate(unsigned& result, unsigned digit, unsigned power, bool isNegative);
string GetErrorMessage(int errorCode);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	bool wasError = false;
	string source = args->sourceNotation;
	string destination = args->destinationNotation;
	string value = args->value;

	int fromRadix = StringToInt(source, 10, wasError);

	if (wasError)
	{
		cout << endl << "Invalid input source" << endl;
		return 1;
	}

	int toRadix = StringToInt(destination, 10, wasError);

	if (wasError)
	{
		cout << endl << "Invalid input destination" << endl;
		return 1;
	}

	string convertedNumber = ConvertNumber(value, fromRadix, toRadix);

	if (!convertedNumber.length())
	{
		return 1;
	}

	cout << endl << value << " = |(" << source << ")->(" << destination << ")| = " << convertedNumber << endl;
	
	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return nullopt;
	}

	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];

	return args;
}

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

	for(char ch : str)
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

int RadixInMaxPower(unsigned radix, int maxExponent, bool isNegative, bool& wasError)
{
	wasError = false;
	double maxPowerValue = pow(static_cast<float>(radix), maxExponent);
	unsigned int maxValue = isNegative ? INT_MAX + 1 : INT_MAX;

	bool highestNumberValueOfRadixBiggerThanMaxInt = maxPowerValue > maxValue;

	if (highestNumberValueOfRadixBiggerThanMaxInt)
	{
		wasError = true;
	}

	return static_cast<int>(maxPowerValue);
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

bool CanAccumulate(unsigned& result, unsigned digit, unsigned power, bool isNegative)
{
	unsigned int maxValue = isNegative ? INT_MAX + 1 : INT_MAX;

	bool overflowDuringMultiplication = digit > maxValue / power;
	bool overflowDuringAddition = result > maxValue - digit * power;

	if (overflowDuringMultiplication || overflowDuringAddition)
	{
		return false;
	}

	result += digit * power;
	return true;
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

string GetErrorMessage(int errorCode)
{
	string errorMessage = "Error: ";

	switch (errorCode)
	{
	case Errors::INVALID_CHAR:
		errorMessage += "invalid character";
		break;
	case Errors::VALUE_OVERFLOW:
		errorMessage += "overflow error";
		break;
	case Errors::EMPTY_STRING:
		errorMessage += "empty string value";
		break;
	case Errors::INVALID_RADIX:
		errorMessage += "invalid radix value";
		break;
	case OUT_OF_RANGE:
		errorMessage += "range error";
		break;
	default:
		errorMessage += "unknown error";
		break;
	}

	return errorMessage;
}