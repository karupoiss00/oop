#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <algorithm>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>

using namespace std;
using namespace boost;
using namespace boost::algorithm;

struct Args
{
	string inputFileName;
	string outputFileName;
	string searchString;
	string replaceString;
};

optional<Args> ParseArgs(int argc, char* argv[]);
string Replace(const string& src, const string& pattern, const string& replace);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	string sourceLine;
	string pattern = argv[3];
	string replace = argv[4];
	

	ifstream input;
	input.open(args->inputFileName);
	
	if (pattern.length() == 0)
	{
		cout << "Argument <search string> should not be empty" << endl;
		return 1;
	}

	if (!input.is_open())
	{
		cout << "Failed to open '" << args->inputFileName << "' for reading\n";
		return 1;
	}

	ofstream output;
	output.open(args->outputFileName);

	if (!output.is_open())
	{
		cout << "Failed to open '" << args->outputFileName << "' for writing\n";
		return 1;
	}


	while (getline(input, sourceLine))
	{
		output << Replace(sourceLine, pattern, replace);
		if (!input.eof())
		{
			output << endl;
		}
	}


	if (input.bad())
	{
		cout << "Falied to read data from input file\n";
		return 1;
	}

	if (!output.flush())
	{
		cout << "Failed to write data to output file\n";
		return 1;
	}

	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: Replace.exe <input file name> <output file name> <search string> <replace string>\n";
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}

string Replace(const string& src, const string& pattern, const string& replace)
{
	string replacedSrc;

	auto searchForPattern = make_knuth_morris_pratt(pattern);
	string::const_iterator prevPos = src.cbegin();
	string::const_iterator nextPos = searchForPattern(prevPos, src.cend());

	while (nextPos != src.cend())
	{
		replacedSrc += src.substr(prevPos - src.cbegin(), nextPos - prevPos);
		replacedSrc += replace;
		prevPos = nextPos + pattern.length();
		nextPos = searchForPattern(prevPos, src.cend());
	}

	replacedSrc += src.substr(prevPos - src.cbegin(), src.cend() - prevPos);
	return replacedSrc;
}