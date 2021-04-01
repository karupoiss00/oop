#include <iostream>
#include <optional>
#include "PrimesGenerator.h"

using namespace std;

struct Args
{
	size_t upperBound;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	

	if (args->upperBound < 2)
	{
		cout << "Ivalid argument!" << endl;
		return 1;
	}

	set<size_t>	primes = GeneratePrimeNumbersSet(args->upperBound);

	for (auto primeNumber : primes)
	{
		cout << primeNumber << " ";
	}

	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: set_of_primes.exe <upperBound>\n";
		return nullopt;
	}

	Args args;
	args.upperBound = atoi(argv[1]);

	return args;
}