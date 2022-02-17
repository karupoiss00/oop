#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include "CryptStream.h"

using namespace std;

struct Args
{
	Operations operation;
	string inputFileName;
	string outputFileName;
	CryptingKey key;
};

optional<Args> ParseArgs(int argc, char* argv[]);
bool IsKeyValueVaild(int key);
bool IsOperationNameValid(const string & operation);
void CryptFile(const string & inputFileName, const string & outputFileName, CryptingKey key, bool & withError);
void DecryptFile(const string & inputFileName, const string & outputFileName, CryptingKey key, bool & withError);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	bool wasError = false;
	
	if (args->operation == Operations::Crypt)
	{
		CryptFile(args->inputFileName, args->outputFileName, args->key, wasError);
	}
	else
	{
		DecryptFile(args->inputFileName, args->outputFileName, args->key, wasError);
	}

	if (wasError)
	{
		return 1;
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
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	
	const string operationName = argv[1];

	if (!IsOperationNameValid(operationName))
	{
		cout << "Error! Unknown operation." << endl;
		cout << "Please, use \"crypt\" or \"decrypt\" as first argument." << endl;
		return nullopt;
	}

	if (!operationName.compare(CRYPT_OPERATION_NAME))
	{
		args.operation = Operations::Crypt;
	}
	else
	{
		args.operation = Operations::Decrypt;
	}

	try 
	{
		int keyValue = atoi(argv[4]);
		if (!IsKeyValueVaild(keyValue))
		{
			cout << "Error! Key must be number in range from 0 to 255." << endl;
			return nullopt;
		}
	}
	catch (std::exception const& e) 
	{
		cout << "Error while parsing key: " << e.what() << endl;
		cout << "Key must have type number." << endl;
		return nullopt;
	}

	return args;
}

bool AreEqualStrings(const string& s1, const string& s2) 
{
	return !s1.compare(s2);
}

bool IsOperationNameValid(const string& operation) 
{
	bool isCryptOperation = !operation.compare(CRYPT_OPERATION_NAME);
	bool isDeryptOperation = !operation.compare(DECRYPT_OPERATION_NAME);
	return isCryptOperation || isDeryptOperation;
}

bool IsKeyValueVaild(int key) 
{
	bool isValueInRange = key >= 0 && key <= 255;
	return isValueInRange;
}

void CryptFile(const string& inputFileName, const string& outputFileName, CryptingKey key, bool & wasError)
{
	ifstream input;
	input.open(inputFileName, ios::binary);

	if (!input.is_open())
	{
		cout << "Failed to open '" << inputFileName << "' for reading" << endl;
		wasError = true;
		return;
	}

	ofstream output;
	output.open(outputFileName, ios::binary);

	if (!output.is_open())
	{
		cout << "Failed to open '" << outputFileName << "' for writing" << endl;
		wasError = true;
		return;
	}

	CryptStream(input, output, key);

	if (input.bad())
	{
		cout << "Falied to read data from input file\n";
		wasError = true;
		return;
	}

	if (!output.flush())
	{
		cout << "Failed to write data to output file\n";
		wasError = true;
		return;
	}

	return;
}

void DecryptFile(const string & inputFileName, const string & outputFileName, const CryptingKey key, bool & wasError)
{
	ifstream input;
	input.open(inputFileName, ios::binary);

	if (!input.is_open())
	{
		cout << "Failed to open '" << inputFileName << "' for reading" << endl;
		wasError = true;
		return;
	}

	ofstream output;
	output.open(outputFileName, ios::binary);

	if (!output.is_open())
	{
		cout << "Failed to open '" << outputFileName << "' for writing" << endl;
		wasError = true;
		return;
	}

	DecryptStream(input, output, key);

	if (input.bad())
	{
		cout << "Falied to read data from input file\n";
		wasError = true;
		return;
	}

	if (!output.flush())
	{
		cout << "Failed to write data to output file\n";
		wasError = true;
		return;
	}

	return;
}