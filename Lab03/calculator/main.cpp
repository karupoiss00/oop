#include <iostream>
#include "CalculatorController.h"

using namespace std;

int main(int argc, char* argv[])
{
	Calculator calculator;
	CalculatorController calculatorControl(calculator, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		try
		{
			if (!calculatorControl.HandleCommand())
			{
				cout << "unknown operation" << endl;
			}
		}
		catch (std::exception const& e)
		{
			cout << e.what() << endl;
		}
	}

	return 0;
}