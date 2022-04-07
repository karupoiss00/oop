#include <iostream>
#include <optional>
#include <cassert>
#include "UrlParser.h"

using namespace std;

string StringToLowerCase(const string& s) 
{
	string result = s;
	std::transform(result.begin(), result.end(), result.begin(),
		[](char c)
		{
			return std::tolower(c); 
		}
	);
	return result;
}

optional<Protocol> MapStringToProtocol(const string& protocol)
{
	string ignoredCaseProtocol = StringToLowerCase(protocol);

	if (ignoredCaseProtocol == "http")
	{
		return Protocol::HTTP;
	}

	if (ignoredCaseProtocol == "https")
	{
		return Protocol::HTTPS;
	}

	if (ignoredCaseProtocol == "ftp")
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
	default:
		assert(false);
		return 0;
	}
}

optional<unsigned> ParsePortFromString(string portStr)
{
	try
	{
		unsigned parsedPort = stoi(portStr);
		if (!IsValidPort(parsedPort))
		{
			return nullopt;
		}
		else
		{
			return parsedPort;
		}
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
		return nullopt;
	}
}

optional<unsigned> ParsePort(string portMatch, Protocol protocol)
{
	if (!portMatch.empty())
	{
		auto parsedPortOpt = ParsePortFromString(portMatch);
		if (parsedPortOpt)
		{
			return parsedPortOpt.value();
		}
		return nullopt;
	}
	
	return MapProtocolToPort(protocol);
}

bool ProcessMatches(const smatch& matches, Protocol& protocol, unsigned& port, string& host, string& document)
{
	if (matches.size() != MATCHES_COUNT)
	{
		return false;
	}

	const auto parsedProtocolOpt = MapStringToProtocol(matches[PROTOCOL_MATCH]);

	if (!parsedProtocolOpt)
	{
		return false;
	}
	
	Protocol parsedProtocol = parsedProtocolOpt.value();

	const auto parsedPortOpt = ParsePort(matches[PORT_MATCH], parsedProtocol);

	if (!parsedPortOpt)
	{
		return false;
	}

	unsigned parsedPort = parsedPortOpt.value();

	if (!matches[HOST_MATCH].length())
	{
		return false;
	}

	host = matches[HOST_MATCH];
	protocol = parsedProtocol;
	port = parsedPort;
	document = matches[DOCUMENT_MATCH];
	
	return true;
}

bool ParseURL(string const& url, Protocol& protocol, unsigned& port, string& host, string& document)
{
	const regex urlRegExp(URL_REGULAR_EXPRESSION, std::regex_constants::icase);

	smatch matches;
	bool matchesFound = regex_search(url, matches, urlRegExp);

	if (!matchesFound)
	{
		return false;
	}

	return ProcessMatches(matches, protocol, port, host, document);
}