#include <iostream>
#include <string>
#include <optional>
#include "UrlParser.h"

using namespace std;

struct Args
{
	string url;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	Protocol protocol;
	unsigned port;
	string host;
	string document;

	if (ParseURL(args->url, protocol, port, host, document))
	{
		cout << args->url << endl;
		cout << "HOST: " << host << endl;
		cout << "PORT: " << port << endl;
		cout << "DOC: " << document << endl;
	}
	else
	{
		cout << "Error: invalid url" << endl;
	}

	return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count" << endl;
		cout << "Usage: url_parser.exe <url>" << endl;
		return nullopt;
	}

	Args args;
	args.url = argv[1];

	return args;
}