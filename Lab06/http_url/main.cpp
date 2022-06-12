#include <iostream>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

std::ostream& operator<<(std::ostream& output, CHttpUrl const& rhs);

int main()
{
	string url;
	while (!cin.eof() && !cin.fail())
	{
		getline(cin, url);
		try
		{
			CHttpUrl parsedUrl(url);
			cout << parsedUrl;
		}
		catch (exception const& e)
		{
			cout << e.what() << endl;
		}
	}

	return 0;
}

std::ostream& operator<<(std::ostream& output, CHttpUrl const& rhs)
{
	output << endl;
	output << "URL: " << rhs.GetURL() << endl;
	output << "PROTOCOL: " << CHttpUrl::MapProtocolToString(rhs.GetProtocol()) << endl;
	output << "DOMAIN: " << rhs.GetDomain() << endl;
	output << "PORT: " << rhs.GetPort() << endl;
	output << "DOC: " << rhs.GetDocument() << endl;
	output << endl;

	return output;
}