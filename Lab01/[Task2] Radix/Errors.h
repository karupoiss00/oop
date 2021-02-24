#pragma once
#include <string>

enum Errors
{
	INVALID_CHAR = 1,
	VALUE_OVERFLOW,
	EMPTY_STRING,
	INVALID_RADIX,
	OUT_OF_RANGE
};

std::string GetErrorMessage(int errorCode);