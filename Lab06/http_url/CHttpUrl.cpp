#include <iostream>
#include <optional>
#include <regex>
#include <cassert>
#include "CUrlParsingError.h"
#include "CHttpUrl.h"

using namespace std;

string StringToLowerCase(const string& s)
{
	string result = s;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c)
	{
		return std::tolower(c);
	}
	);
	return result;
}

bool IsValidPort(unsigned short port)
{
	return port > 0 && port <= 65535;
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	const regex urlRegExp(URL_REGULAR_EXPRESSION, std::regex_constants::icase);

	smatch matches;
	bool matchesFound = regex_search(url, matches, urlRegExp);

	if (matches.size() != MATCHES_COUNT)
	{
		throw CUrlParsingError("unknown url format");
	}

	if (!matches[HOST_MATCH].length())
	{
		throw CUrlParsingError("domain not found");
	}

	ParseProtocol(matches[PROTOCOL_MATCH]);
	ParsePort(matches[PORT_MATCH]);
	m_domain = matches[HOST_MATCH];
	m_document = '/' + matches[DOCUMENT_MATCH].str();
}

void CHttpUrl::ParseProtocol(string const& protocol)
{
	string caseInsensetiveProtocol = StringToLowerCase(protocol);

	if (caseInsensetiveProtocol == "http")
	{
		m_protocol = Protocol::HTTP;
		return;
	}

	if (caseInsensetiveProtocol == "https")
	{
		m_protocol = Protocol::HTTPS;
		return;
	}

	throw CUrlParsingError("error while parsing protocol");
}

void CHttpUrl::SetPortByProtocol()
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		m_port = 80;
		break;
	case Protocol::HTTPS:
		m_port = 443;
		break;
	default:
		assert(false);
	}
}

void CHttpUrl::ParsePort(string const& port)
{
	if (port.empty())
	{
		SetPortByProtocol();
		return;
	}

	try
	{
		int parsedPort = stoi(port);
		if (!IsValidPort(parsedPort))
		{
			throw CUrlParsingError("error while parsing port");
		}
		else
		{
			m_port = static_cast<unsigned short>(parsedPort);
		}
	}
	catch (std::exception const& e)
	{
		throw CUrlParsingError("error while parsing port");
	}
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}