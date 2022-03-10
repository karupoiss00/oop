#pragma once
#include <string>
#include <regex>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP,
};

bool ParseURL(std::string const& url, Protocol& protocol, unsigned& port, std::string& host, std::string& document);