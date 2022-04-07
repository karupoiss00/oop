#include <iostream>
#include <string>
#include <optional>
#include "UrlParser.h"

using namespace std;

int main(int argc, char* argv[])
{
	string url;
	Protocol protocol;
	unsigned port;
	string host;
	string document;
	
	while (!cin.eof() && !cin.fail())
	{
		getline(cin, url);
		if (ParseURL(url, protocol, port, host, document))
		{
			cout << "HOST: " << host << endl;
			cout << "PORT: " << port << endl;
			cout << "DOC: " << document << endl;
		}
		else
		{
			cout << "Error: invalid url" << endl;
		}
		cout << endl;
	}

	return 0;
}