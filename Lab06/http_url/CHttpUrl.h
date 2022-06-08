#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};

using Port = unsigned short;

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

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	CHttpUrl
	(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP
	);

	CHttpUrl
	(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		Port port
	);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;

	void ParseProtocol(std::string const& protocol);
	void ParseDomain(std::string const& domain);
	void ParsePort(std::string const& port);
	void ParseDocument(std::string const& document);
	
	void SetPortByProtocol();

	std::string MapProtocolToString() const;
};
