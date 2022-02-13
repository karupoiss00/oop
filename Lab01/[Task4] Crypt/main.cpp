#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include "CryptStream.h"
#include "OperationNames.h"

using namespace std;

struct Args
{
	string operationName;
	string inputFileName;
	string outputFileName;
	int key;
};

optional<Args> ParseArgs(int argc, char* argv[]);
bool verifyKeyValue(int key);
bool verifyOperationName(const string& operation);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	if (!verifyOperationName(args->operationName))
	{
		cout << "Error! Unknown operation." << endl;
		cout << "Please, use \"crypt\" or \"decrypt\" as first argument." << endl;
		return 1;
	}

	if (!verifyKeyValue(args->key)) 
	{
		cout << "Error! Key must be number in range from 0 to 255." << endl;
		return 1;
	}

	CryptingKey cryptingKey = static_cast<CryptingKey>(args->key);

	ifstream input;
	input.open(args->inputFileName, ios::binary);

	if (!input.is_open())
	{
		cout << "Failed to open '" << args->inputFileName << "' for reading" << endl;
		return 1;
	}

	ofstream output;
	output.open(args->outputFileName, ios::binary);

	if (!output.is_open())
	{
		cout << "Failed to open '" << args->outputFileName << "' for writing" << endl;
		return 1;
	}

	if (!args->operationName.compare(CRYPT_OPERATION))
	{
		CryptStream(input, output, cryptingKey);
	}
	else
	{
		DecryptStream(input, output, cryptingKey);
	}

	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: crypt.exe <crypt/decrypt> <input file> <output file> <key>" << endl;
		return nullopt;
	}

	Args args;
	args.operationName = argv[1];
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	
	try {
		args.key = atoi(argv[4]);
	}
	catch (std::exception const& e) {
		cout << "Error while parsing key: " << e.what() << endl;
		cout << "Key must have type number." << endl;
		return nullopt;
	}

	return args;
}

bool areEqualStrings(const string& s1, const string& s2) {
	return !s1.compare(s2);
}

bool verifyOperationName(const string& operation) 
{
	bool isCryptOperation = !operation.compare(CRYPT_OPERATION);
	bool isDeryptOperation = !operation.compare(DECRYPT_OPERATION);
	return isCryptOperation || isDeryptOperation;
}

bool verifyKeyValue(int key) 
{
	bool isValueInRange = key >= 0 && key <= 255;
	return isValueInRange;
}

/*
	TODO: полирнуть код
	TODO: тесты тест тесты
*/