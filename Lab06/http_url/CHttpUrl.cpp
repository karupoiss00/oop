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

bool IsValidPort(Port port)
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

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol)
{
	m_protocol = protocol;
	try
	{
		ParseDomain(domain);
		SetPortByProtocol();
		ParseDocument(document);
	}
	catch (exception const& e)
	{
		throw invalid_argument(e.what());
	}
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, Port port)
	: CHttpUrl(domain, document, protocol)
{
	if (!IsValidPort(port))
	{
		throw CUrlParsingError("invalid port");
	}

	m_port = port;
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

void CHttpUrl::ParseDomain(std::string const& domain)
{
	const regex domainRegExp(DOMAIN_REGULAR_EXPRESSION, std::regex_constants::icase);
	smatch matches;
	bool matchesFound = regex_search(domain, matches, domainRegExp);

	if (!matchesFound)
	{
		throw CUrlParsingError("invalid domain");
	}

	m_domain = matches[1];
}

void CHttpUrl::SetPortByProtocol()
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		m_port = DEFAULT_HTTP_PORT;
		break;
	case Protocol::HTTPS:
		m_port = DEFAULT_HTTPS_PORT;
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
			m_port = static_cast<Port>(parsedPort);
		}
	}
	catch (std::exception const&)
	{
		throw CUrlParsingError("error while parsing port");
	}
}

void CHttpUrl::ParseDocument(std::string const& document)
{
	const regex documentRegExp(DOCUMENT_REGULAR_EXPRESSION, std::regex_constants::icase);
	smatch matches;
	bool matchesFound = regex_search(document, matches, documentRegExp);

	if (!matchesFound)
	{
		throw CUrlParsingError("invalid document");
	}
	string parsedDocument = matches[1];

	if (parsedDocument[0] != '/')
	{
		parsedDocument = '/' + parsedDocument;
	}

	m_document = parsedDocument;
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

Port CHttpUrl::GetPort() const
{
	return m_port;
}

string CHttpUrl::MapProtocolToString() const
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		assert(false);
		return "";
	}
}

string CHttpUrl::GetURL() const
{
	string protocol = MapProtocolToString();
	bool urlHasCutomPort = 
		m_port != DEFAULT_HTTP_PORT 
		&& m_port != DEFAULT_HTTPS_PORT;

	string url = protocol + "://"s + m_domain;

	if (urlHasCutomPort)
	{
		url += ':' + to_string(m_port);
	}

	url += m_document;

	return url;
}