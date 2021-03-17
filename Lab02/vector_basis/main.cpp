//Прибавить к каждому элементу массива сумму трех минимальных элементов массива
#include "VectorProcessor.h"

using namespace std;

int main()
{
	vector<float> inputData;

	if (!ParseFloatsToVector(cin, inputData))
	{
		cout << "Incorrect input data" << endl;
		return 1;
	}

	if (!AddThreeMinElements(inputData))
	{
		cout << "Size of array must be greater than 2" << endl;
		return 1;
	}

	std::sort(inputData.begin(), inputData.end());

	PrintVectorOfFloats(inputData);

	return 0;
}