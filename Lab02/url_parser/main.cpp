#include <iostream>
#include <regex>
#include <optional>

using namespace std;

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
};

bool ParseURL(string const& url, Protocol& protocol, unsigned& port, string& host, string& document);

int main(int argc, char* argv[])
{
	Protocol protocol;
	unsigned port;
	string host;
	string document;

	return 0;
}

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

bool ProcessTwoMatches(const smatch& matches, Protocol& protocol, unsigned& port, string& host, string& document)
{
	if (matches.size() != 2)
	{
		return false;
	}

	const auto protocolFromString = MapStringToProtocol(matches[0]);

	if (!protocolFromString)
	{
		return false;
	}

	protocol = protocolFromString.value();
	host = matches[1];
	port = MapProtocolToPort(protocolFromString.value());
	document = "/";

	return true;
}

bool ProcessThreeMatches(const smatch& matches, Protocol& protocol, unsigned& port, string& host, string& document)
{
	if (matches.size() != 3)
	{
		return false;
	}

	const auto protocolFromString = MapStringToProtocol(matches[0]);

	if (!protocolFromString)
	{
		return false;
	}

	string portOrDocument = matches[2];

	if (portOrDocument[0] == ':')
	{
		try
		{
			port = stoi(portOrDocument.substr(1, portOrDocument.length() - 1));
		}
		catch (std::exception e)
		{
			cout << e.what() << endl;
			return false;
		}
	}
	else
	{
		document = portOrDocument;
		port = MapProtocolToPort(protocolFromString.value());
	}

	protocol = protocolFromString.value();
	host = matches[1];

	return true;
}

bool ProcessFourMatches(const smatch& matches, Protocol& protocol, unsigned& port, string& host, string& document)
{
	if (matches.size() != 4)
	{
		return false;
	}

	const auto protocolFromString = MapStringToProtocol(matches[0]);

	if (!protocolFromString)
	{
		return false;
	}

	try
	{
		port = stoi(matches[2]);
	}
	catch (std::exception e)
	{
		cout << e.what() << endl;
		return false;
	}

	protocol = protocolFromString.value();
	host = matches[1];
	document = matches[3];

	return true;
}

bool ParseURL(string const& url, Protocol& protocol, unsigned& port, string& host, string& document)
{
	const regex urlRegExp(
		R"(
		^(https|http|ftp)?
		:\/\/
		([\w-]{1,63}(?:\.[\w-]{1,63})+)
		(:\d{1,5})?
		(\/[^\s@]*)*$
	)");

	smatch matches;
	bool matchesFound = regex_search(url, matches, urlRegExp);

	if (!matchesFound)
	{
		return false;
	}

	switch (matches.size())
	{
		case 2:
			return ProcessTwoMatches(matches, protocol, port, host, document);
		case 3:
			return ProcessThreeMatches(matches, protocol, port, host, document);
		case 4:
			return ProcessFourMatches(matches, protocol, port, host, document);
		default:
			return false;
	}
}