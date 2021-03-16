//Прибавить к каждому элементу массива сумму трех минимальных элементов массива
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool ParseFloatsToVector(istream& input, vector<float>& v);
bool AddThreeMinElements(vector<float>& v);
void PrintVectorOfFloats(const vector<float>& v);

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

bool ParseFloatsToVector(istream& input, vector<float>& v)
{
	string inputStr;
	float value;

	while (input >> inputStr)
	{
		std::istringstream strm(inputStr);
		float value;
		if (strm >> value)
		{
			v.push_back(value);
		}
		else
		{
			return false;
		}

	}

	return true;
}

bool AddThreeMinElements(vector<float>& v)
{
	vector<float> vCopy = v;
	std::sort(vCopy.begin(), vCopy.end());

	if (v.size() < 3)
	{
		return false;
	}

	const float sumOfMinElements = vCopy[0] + vCopy[1] + vCopy[2];
	
	for (float& elem : v)
	{
		elem += sumOfMinElements;
	}
	return true;
}

void PrintVectorOfFloats(const vector<float>& v)
{
	for (float elem : v)
	{
		cout << elem << " ";
	}
}