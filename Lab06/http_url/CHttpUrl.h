#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};

using Port = unsigned short;

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
	Port GetPort() const;

	static std::string MapProtocolToString(Protocol protocol);
	static bool IsValidPort(int port);
private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	Port m_port;
	// сделать статическими либо константными, либо поместить в безымянное пространство
	Protocol ParseProtocol(std::string const& protocol);
	std::string ParseDomain(std::string const& domain);
	Port ParsePort(std::string const& port);
	std::string ParseDocument(std::string const& document);

	static Port MapProtocolToPort(Protocol protocol);
};	