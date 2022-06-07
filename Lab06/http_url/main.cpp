#include <iostream>
#include "CUrlParsingError.h"

using namespace std;

int main()
{
	try
	{
		throw CUrlParsingError("invalid host");
	}
	catch (exception const& e)
	{
		cout << e.what();
	}

	return 0;
}