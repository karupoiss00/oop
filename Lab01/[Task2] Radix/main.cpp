#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <algorithm>
#include "StringIntCasts.h"

using namespace std;

struct Args
{
	string sourceNotation;
	string destinationNotation;
	string value;
};

optional<Args> ParseArgs(int argc, char* argv[]);

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