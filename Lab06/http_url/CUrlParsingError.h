#pragma once
#include <stdexcept>
#include <string>

class CUrlParsingError : public std::invalid_argument
{
public:
	explicit CUrlParsingError(std::string const& what_arg);
};
