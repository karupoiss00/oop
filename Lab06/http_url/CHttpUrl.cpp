#include <iostream>
#include <regex>
#include <cassert>
#include "CUrlParsingError.h"
#include "CHttpUrl.h"

using namespace std;

const Port DEFAULT_HTTP_PORT = 80;
const Port DEFAULT_HTTPS_PORT = 443;

const std::string URL_REGULAR_EXPRESSION = R"(^(https|http)://([\w-]{1,63}(?:\.[\w-]{1,63})*)(?:(?::)(\d{1,5}))?(?:(?:/)([^\s]*))*$)";
const std::string DOMAIN_REGULAR_EXPRESSION = R"(^([\w-]{1,63}(?:\.[\w-]{1,63})*)$)";
const std::string DOCUMENT_REGULAR_EXPRESSION = R"(^(((?:\/)*([^\s]*))*)$)";

constexpr unsigned MATCHES_COUNT = 5;
constexpr unsigned PROTOCOL_MATCH = 1;
constexpr unsigned HOST_MATCH = 2;
constexpr unsigned PORT_MATCH = 3;
constexpr unsigned DOCUMENT_MATCH = 4;

string StringToLowerCase(string s);

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

	m_protocol = ParseProtocol(matches[PROTOCOL_MATCH]);
	m_port = ParsePort(matches[PORT_MATCH]);
	m_domain = matches[HOST_MATCH];
	m_document = '/' + matches[DOCUMENT_MATCH].str();
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol)
{
	m_protocol = protocol;
	try
	{
		m_domain = ParseDomain(domain);
		m_port = MapProtocolToPort(m_protocol);
		m_document = ParseDocument(document);
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

string CHttpUrl::GetURL() const
{
	string protocol = MapProtocolToString(m_protocol);
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

string CHttpUrl::GetDomain() const
{
	return m_domain;
}

string CHttpUrl::GetDocument() const
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

Protocol CHttpUrl::ParseProtocol(string const& protocol)
{
	string caseInsensetiveProtocol = StringToLowerCase(protocol);

	if (caseInsensetiveProtocol == "http")
	{
		return Protocol::HTTP;
	}

	if (caseInsensetiveProtocol == "https")
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("error while parsing protocol");
}

string CHttpUrl::ParseDomain(std::string const& domain)
{
	const regex domainRegExp(DOMAIN_REGULAR_EXPRESSION, std::regex_constants::icase);
	smatch matches;
	bool matchesFound = regex_search(domain, matches, domainRegExp);

	if (!matchesFound)
	{
		throw CUrlParsingError("invalid domain");
	}

	return matches[1];
}

Port CHttpUrl::ParsePort(string const& port)
{
	if (port.empty())
	{
		return MapProtocolToPort(m_protocol);
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
			return static_cast<Port>(parsedPort);
		}
	}
	catch (std::exception const&)
	{
		throw CUrlParsingError("error while parsing port");
	}
}

string CHttpUrl::ParseDocument(std::string const& document)
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

	return parsedDocument;
}

Port CHttpUrl::MapProtocolToPort(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return DEFAULT_HTTP_PORT;
	case Protocol::HTTPS:
		return DEFAULT_HTTPS_PORT;
	default:
		assert(false);
		return 0;
	}
}

string CHttpUrl::MapProtocolToString(Protocol protocol)
{
	switch (protocol)
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

bool CHttpUrl::IsValidPort(int port)
{
	return port > 0 && port <= 65535;
}

string StringToLowerCase(string s)
{
	std::transform(s.begin(), s.end(), s.begin(),
		[](unsigned char c)
	{
		return std::tolower(c);
	}
	);
	return s;
}