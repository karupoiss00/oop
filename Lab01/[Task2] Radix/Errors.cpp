#include "Errors.h"

using namespace std;

string GetErrorMessage(int errorCode)
{
	string errorMessage = "Error: ";

	switch (errorCode)
	{
	case Errors::INVALID_CHAR:
		errorMessage += "invalid character";
		break;
	case Errors::VALUE_OVERFLOW:
		errorMessage += "overflow error";
		break;
	case Errors::EMPTY_STRING:
		errorMessage += "empty string value";
		break;
	case Errors::INVALID_RADIX:
		errorMessage += "invalid radix value";
		break;
	case OUT_OF_RANGE:
		errorMessage += "range error";
		break;
	default:
		errorMessage += "unknown error";
		break;
	}

	return errorMessage;
}