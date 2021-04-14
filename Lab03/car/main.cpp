#include "CarController.h"
#include "Car.h"

using namespace std;

int main(int argc, char* argv[])
{
	CCar car;
	CCarController carControl(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << endl << "> ";

		if (!carControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}

	return 0;
}