#include <iostream>
#include <ostream>
#include <string>
#include "FindMaxEx.h"

using namespace std;

struct Athlete
{
	Athlete()
		: m_name(""), m_growth(0), m_weight(0)
	{}

	Athlete(string name, double growth, double weight)
		: m_name(name), m_growth(growth), m_weight(weight)
	{}

	string m_name;
	double m_growth;
	double m_weight;
};

void CreateAthletes(vector<Athlete>& athletes);
void PrintMaxWeightAthlete(vector<Athlete> const& athletes);
void PrintMaxGrowthAthlete(vector<Athlete> const& athletes);
ostream& operator<<(ostream& output, Athlete const& athlete);

int main(int argc, char* argv[])
{
	vector<Athlete> athletes;
	CreateAthletes(athletes);

	PrintMaxWeightAthlete(athletes);
	PrintMaxGrowthAthlete(athletes);

	cout << endl;

	return 0;
}

ostream& operator<<(ostream& output, Athlete const& athlete)
{
	output << athlete.m_name << endl;
	output << "Weight: " << athlete.m_weight << "cm" << endl;
	output << "Growth: " << athlete.m_growth << "kg";

	return output;
}

void CreateAthletes(vector<Athlete>& athletes)
{
	athletes.insert(athletes.end(), Athlete("Ivan Petrov", 180.5, 60));
	athletes.insert(athletes.end(), Athlete("Pig Petr", 150, 80.7));
	athletes.insert(athletes.end(), Athlete("Viktor Ivanov", 167.1, 70.3));
}

void PrintMaxWeightAthlete(vector<Athlete> const& athletes)
{
	auto LessWeight = [](Athlete const& lhs, Athlete const& rhs) 
	{
		return lhs.m_weight < rhs.m_weight;
	};

	Athlete athleteWithMaxWeight;

	FindMax(athletes, athleteWithMaxWeight, LessWeight);

	cout << endl << "Athlete with max weight: " << athleteWithMaxWeight << endl;
}

void PrintMaxGrowthAthlete(vector<Athlete> const& athletes)
{
	auto LessGrowth = [](Athlete const& lhs, Athlete const& rhs)
	{
		return lhs.m_growth < rhs.m_growth;
	};

	Athlete athleteWithMaxGrowth;

	FindMax(athletes, athleteWithMaxGrowth, LessGrowth);

	cout << endl << "Athlete with max growth: " << athleteWithMaxGrowth << endl;
}