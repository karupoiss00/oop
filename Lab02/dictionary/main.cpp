#include <iostream>
#include <optional>
#include "Dictionary.h"
#include "DialogConsts.h"

using namespace std;

struct Args
{
	string dictionaryFilename;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	Dictionary dictionary;
	size_t startSize;

	LoadDictionary(args->dictionaryFilename, dictionary);
	startSize = dictionary.size();

	StartSessionWithUser(dictionary, Input, Output);

	if (startSize != dictionary.size())
	{
		if (NeedDictionarySaving(Input, Output))
		{
			SaveDictionary(args->dictionaryFilename, dictionary);
			cout << MSG_CHANGES_SAVED << " ";
		}
	}

	cout << MSG_BYE;

	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: dictionary.exe <dictionary>\n";
		return nullopt;
	}

	Args args;
	args.dictionaryFilename = argv[1];

	return args;
}