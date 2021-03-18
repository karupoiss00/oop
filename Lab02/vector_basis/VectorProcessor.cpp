#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorOfFloats(const vector<float>& v)
{
	std::for_each(v.cbegin(), v.cend(), [](const float& elem)
	{
		cout << elem, " ";
	});
}

bool ParseFloatsToVector(istream& input, vector<float>& v)
{
	float value = 0.f;

	while (input >> value && !input.eof())
	{
		v.push_back(value);
	}
	
	if (!input.eof())
	{
		return false;
	}

	return v.size() > 0 ? true : false;
}

bool AddThreeMinElements(vector<float>& v)
{
	if (v.size() < 3)
	{
		return false;
	}

	vector<float> vCopy = v;
	std::partial_sort(vCopy.begin(), vCopy.begin() + 3, vCopy.end());

	const float sumOfMinElements = vCopy[0] + vCopy[1] + vCopy[2];

	std::for_each(v.begin(), v.end(), [sumOfMinElements](float& elem)
	{
		elem += sumOfMinElements;
	});
	return true;
}

