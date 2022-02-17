#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <functional>
#include "CryptStream.h"

using namespace std;

using TranformerFn = std::function<void(istream& input, ostream& output)>;

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
void TranformFile(const string& inputFileName, const string& outputFileName,
	TranformerFn transformerFn, bool& wasError);

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
		TranformFile(args->inputFileName, args->outputFileName,
			[args](istream& input, ostream& output)
			{
				CryptStream(input, output, args->key);
			},
			wasError);
	}
	else
	{
		TranformFile(args->inputFileName, args->outputFileName,
			[args](istream& input, ostream& output)
			{
				DecryptStream(input, output, args->key);
			},
			wasError);
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
	args.operation = operationsMap.find(operationName)->second;

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

bool IsOperationNameValid(const string& operation) 
{
	bool isCryptOperation = operation == CRYPT_OPERATION_NAME;
	bool isDeryptOperation = operation == DECRYPT_OPERATION_NAME;
	return isCryptOperation || isDeryptOperation;
}

bool IsKeyValueVaild(int key) 
{
	bool isValueInRange = key >= 0 && key <= 255;
	return isValueInRange;
}

void TranformFile(const string& inputFileName, const string& outputFileName,
	TranformerFn transformerFn, bool& wasError)
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

	transformerFn(input, output);

	if (input.bad())
	{
		cout << "Falied to read data from input file" << endl;
		wasError = true;
		return;
	}

	if (!output.flush())
	{
		cout << "Failed to write data to output file" << endl;
		wasError = true;
		return;
	}

	return;
}