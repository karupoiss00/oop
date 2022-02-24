#include <iostream>
#include <optional>
#include <sstream>
#include <istream>
#include <fstream>
#include "Labyrinth.h"

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[]);
optional<Labyrinth> ReadLabyrinthFromFile(const string& inputFileName);
void WriteLabyrinthToFile(const string& outputFileName, const Labyrinth& labyrinth, bool& wasError);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	auto labyrinth = ReadLabyrinthFromFile(args->inputFileName);

	if (!labyrinth)
	{
		return 1;
	}

	bool wasError = false;

	PaveShortestWay(labyrinth.value(), wasError);

	if (wasError)
	{
		return 1;
	}

	WriteLabyrinthToFile(args->outputFileName, labyrinth.value(), wasError);

	if (wasError)
	{
		return 1;
	}

	return 0;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: labyrinth.exe <input file> <output file>" << endl;
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
};

optional<Labyrinth> ReadLabyrinthFromFile(const string& inputFileName)
{
	ifstream inputFile;
	inputFile.open(inputFileName, ios::binary);

	if (!inputFile.is_open())
	{
		cout << "Failed to open '" << inputFileName << "' for reading" << endl;
		return nullopt;
	}

	auto labyrinth = ReadLabyrinth(inputFile);

	inputFile.close();

	return labyrinth;
};

void WriteLabyrinthToFile(const string& outputFileName, const Labyrinth& labyrinth, bool& wasError)
{
	ofstream outputFile;
	outputFile.open(outputFileName, ios::binary);

	if (!outputFile.is_open())
	{
		cout << "Failed to open '" << outputFileName << "' for writing" << endl;
		wasError = true;
		return;
	}

	WriteLabyrinth(outputFile, labyrinth, wasError);

	outputFile.close();

	return;
};