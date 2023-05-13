#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Body.h"
#include "BodyFactory.h"

using namespace std;

bool CreateBodiesFromFile(const string& fileName, Bodies& bodies);
bool CreateBodiesFromInput(Bodies& bodies);
void ShowInfoAboutBodies(const Bodies& bodies);
void ShowInfoAboutBodyWithMaxMass(const Bodies& bodies);
void ShowInfoAboutBodyWithMinWeightInWater(const Bodies& bodies);
void PrintHelp();

int main(int argc, char* argv[])
{
	Bodies bodies;

	if (argc < 2)
	{
		if (!CreateBodiesFromInput(bodies))
		{
			cout << "Cannot create bodies" << endl;
			return 1;
		}
	}
	else
	{
		if (argv[1] == "--help")
		{
			PrintHelp();
			return 0;
		}

		if (!CreateBodiesFromFile(argv[1], bodies))
		{
			cout << "Cannot create bodies" << endl;
			return 1;
		}
	}

	ShowInfoAboutBodies(bodies);
	ShowInfoAboutBodyWithMaxMass(bodies);
	ShowInfoAboutBodyWithMinWeightInWater(bodies);

	return 0;
}

bool CreateBodiesFromScript(istream& strm, Bodies& bodies)
{
	CBodyFactory factory;
	factory.CreateBodies(bodies, strm);

	return true;
}

bool CreateBodiesFromInput(Bodies& bodies)
{
	stringstream strm;
	string str;

	while (!cin.eof() && !cin.fail())
	{
		getline(cin, str);
		strm << str << endl;
	}

	return CreateBodiesFromScript(strm, bodies);
}

bool CreateBodiesFromFile(const string& fileName, Bodies& bodies)
{
	ifstream strm(fileName);

	if (!strm.is_open())
	{
		cout << "Failed to open " << fileName << " for reading" << endl;
		return false;
	}

	return CreateBodiesFromScript(strm, bodies);
}

void ShowInfoAboutBodies(const Bodies& bodies)
{
	for (const auto& body : bodies)
	{
		cout << body->ToString();
	}
}

body_ptr BodyWithMaxMass(const Bodies& bodies)
{
	if (!bodies.size())
	{
		return nullptr;
	}

	auto CompareBodies = [](body_ptr const& a, body_ptr const& b) -> bool
	{
		return a->GetMass() < b->GetMass();
	};

	auto body = max_element(bodies.begin(), bodies.end(), CompareBodies);

	return *body;
}

void ShowInfoAboutBodyWithMaxMass(const Bodies& bodies)
{
	cout << endl << "Body with maximum mass:" << endl;
	auto body = BodyWithMaxMass(bodies);

	if (body != nullptr)
	{
		cout << body->ToString();
	}
}

body_ptr BodyWithMinWeightInWater(const Bodies& bodies)
{
	if (!bodies.size())
	{
		return nullptr;
	}

	const double g = 9.80665;
	const double waterDensity = 1000;

	auto CompareBodies = [&](body_ptr const& a, body_ptr const& b) -> bool
	{
		double aWeight = a->GetVolume() * (a->GetDensity() - waterDensity) * g;
		double bWeight = b->GetVolume() * (b->GetDensity() - waterDensity) * g;

		return aWeight < bWeight;
	};

	auto body = min_element(bodies.begin(), bodies.end(), CompareBodies);

	return *body;
}

void ShowInfoAboutBodyWithMinWeightInWater(const Bodies& bodies)
{
	cout << endl << "Body with minimum weight in water:" << endl;
	auto body = BodyWithMinWeightInWater(bodies);

	if (body != nullptr)
	{
		cout << body->ToString();
	}
}

void PrintHelp()
{
	cout << "Usage: bodies.exe <script file>" << endl;
	cout << "Use following syntax and commands to create bodies:" << endl << endl;
	cout << "{" << endl << "  sphere <density> <radius>" << endl;
	cout << "  cone <density> <radius of base> <height>" << endl;
	cout << "  cylinder <density> <radius of base> <height>" << endl;
	cout << "  parallelepiped <density> <width> <height> <depth>" << endl;
	cout << "  compound" << endl << "  {" << endl << "    <some body>" << endl;
	cout << "    <some body>" << endl << "    ..." << endl << "  }" << endl;
	cout << "}" << endl;
}