#include <iostream>
#include <string>
#include <string_view>
#include "HtmlDecode.h"

using namespace std;
int main()
{
    string line;
    while (getline(cin, line))
    {
        cout << HtmlDecode(line);
        if (cin.good())
        {
            cout << endl;
        }
    }
}