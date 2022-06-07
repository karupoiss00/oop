#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& what_arg)
	: std::invalid_argument(what_arg)
{

}