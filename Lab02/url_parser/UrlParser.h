#pragma once
#include <string>
#include <regex>

const std::string URL_REGULAR_EXPRESSION = R"(^(https|http|ftp)://([\w-]{1,63}(?:\.[\w-]{1,63})*)(?:(?::)(\d{1,5}))?(?:(?:/)([^\s]*))*$)";
constexpr unsigned MATCHES_COUNT = 5;
constexpr unsigned PROTOCOL_MATCH = 1;
constexpr unsigned HOST_MATCH = 2;
constexpr unsigned PORT_MATCH = 3;
constexpr unsigned DOCUMENT_MATCH = 4;

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
};

bool ParseURL(std::string const& url, Protocol& protocol, unsigned& port, std::string& host, std::string& document);