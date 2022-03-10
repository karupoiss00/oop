#include <iostream>
#include <optional>
#include "UrlParser.h"

using namespace std;

optional<Protocol> MapStringToProtocol(const string& protocol)
{
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}

	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}

	if (protocol == "ftp")
	{
		return Protocol::FTP;
	}

	return nullopt;
}

bool IsValidPort(unsigned port)
{
	return port > 0 && port <= 65535;
}

unsigned MapProtocolToPort(const Protocol& protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	case Protocol::FTP:
		return 21;
	}
}

string TrimFirstChar(const string& str)
{
	return str.substr(1, str.length() - 1);
}

bool ProcessMatches(const smatch& matches, Protocol& protocol, unsigned& port, string& host, string& document)
{
	const auto protocolFromString = MapStringToProtocol(matches[1]);

	if (!protocolFromString)
	{
		return false;
	}

	try
	{
		string portStr = matches[3].str();
		if (!portStr.length())
		{
			port = MapProtocolToPort(protocolFromString.value());
		}
		else
		{
			port = stoi(TrimFirstChar(portStr));
			if (!IsValidPort(port))
			{
				return false;
			}
		}
	}
	catch (std::exception e)
	{
		cout << e.what() << endl;
		return false;
	}

	protocol = protocolFromString.value();

	if (!matches[2].length())
	{
		return false;
	}

	host = matches[2];

	if (matches[4].length())
	{
		document = TrimFirstChar(matches[4]);
	}
	else
	{
		document = "";
	}
	
	return true;
}

bool ParseURL(string const& url, Protocol& protocol, unsigned& port, string& host, string& document)
{
	const regex urlRegExp(
		R"(^(https|http|ftp)?://([\w-]{1,63}(?:\.[\w-]{1,63})+)(:\d{1,5})?(/[^\s@]*)*$)"
	);

	smatch matches;
	bool matchesFound = regex_search(url, matches, urlRegExp);

	for (unsigned i = 0; i < matches.size(); i++)
	{
		cout << matches[i] << endl;
	}

	if (!matchesFound)
	{
		return false;
	}

	return ProcessMatches(matches, protocol, port, host, document);
}