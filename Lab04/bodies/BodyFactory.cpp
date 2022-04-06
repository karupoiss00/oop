#include <sstream>
#include <regex>
#include <functional>
#include <vector>
#include "BodyFactory.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Parallelepiped.h"
#include "Compound.h"

using namespace std;
using namespace std::placeholders;

CBodyFactory::CBodyFactory()
	: m_nestingLevel(0), m_openDelimiter('{'), m_closeDelimiter('}') {}


void CBodyFactory::CreateBodies(Bodies& bodies, istream& strm)
{
	string line;
	vector<double> args;

	CreateActionMap(args, strm);
	getline(strm, line);

	if (!IsOpenDelimiter(line))
	{
		return;
	}

	while (getline(strm, line))
	{
		if (IsCloseDelimiter(line))
		{
			return;
		}

		string&& action = GetAction(line);
		GetActionArgs(args, line);
		ExecuteAction(bodies, action, args);
	}
}

void CBodyFactory::CreateActionMap(const vector<double>& args, istream& strm)
{
	m_actionMap.clear();
	m_actionMap.insert(make_pair("sphere", bind(&CBodyFactory::CreateSphere, this, ref(args))));
	m_actionMap.insert(make_pair("cone", bind(&CBodyFactory::CreateCone, this, ref(args))));
	m_actionMap.insert(make_pair("cylinder", bind(&CBodyFactory::CreateCylinder, this, ref(args))));
	m_actionMap.insert(make_pair("parallelepiped", bind(&CBodyFactory::CreateParallelepiped, this, ref(args))));
	m_actionMap.insert(make_pair("compound", bind(&CBodyFactory::CreateCompound, this, ref(strm))));
}

body_ptr CBodyFactory::CreateSphere(const vector<double>& args)
{
	if (args.size() != 2)
	{
		return nullptr;
	}

	shared_ptr<CSphere> body(new CSphere(args[0], args[1]));
	body->SetNestingLevel(m_nestingLevel + 2);

	return body;
}

body_ptr CBodyFactory::CreateCone(const vector<double>& args)
{
	if (args.size() != 3)
	{
		return nullptr;
	}

	shared_ptr<CCone> body(new CCone(args[0], args[1], args[2]));
	body->SetNestingLevel(m_nestingLevel + 2);

	return body;
}

body_ptr CBodyFactory::CreateCylinder(const vector<double>& args)
{
	if (args.size() != 3)
	{
		return nullptr;
	}

	shared_ptr<CCylinder> body(new CCylinder(args[0], args[1], args[2]));
	body->SetNestingLevel(m_nestingLevel + 2);

	return body;
}

body_ptr CBodyFactory::CreateParallelepiped(const vector<double>& args)
{
	if (args.size() != 4)
	{
		return nullptr;
	}

	shared_ptr<CParallelepiped> body(new CParallelepiped(args[0], args[1], args[2], args[3]));
	body->SetNestingLevel(m_nestingLevel + 2);

	return body;
}

body_ptr CBodyFactory::CreateCompound(istream& strm)
{
	Bodies bodies;
	CBodyFactory factory;

	factory.CreateBodies(bodies, strm);

	shared_ptr<CCompound> body(new CCompound());
	body->SetNestingLevel(m_nestingLevel + 2);

	for (size_t i = 0; i < bodies.size(); ++i)
	{
		bodies[i]->SetNestingLevel(m_nestingLevel + 4);
		body->AddChildBody(bodies[i]);
	}

	return body;
}

string CBodyFactory::GetAction(string& line)
{
	smatch searchResult;
	regex rgx("[A-Za-z]+");

	if (regex_search(line, searchResult, rgx))
	{
		string action = searchResult.str();
		line = searchResult.suffix().str();

		return action;
	}
	return "";
}

void CBodyFactory::GetActionArgs(vector<double>& args, const string& line)
{
	stringstream strm(line);
	args.clear();
	args.insert(args.begin(), istream_iterator<double>(strm), istream_iterator<double>());
}

bool CBodyFactory::ExecuteAction(Bodies& bodies, const string& action, const vector<double>& args)
{
	if (m_actionMap.find(action) == m_actionMap.end())
	{
		return false;
	}

	body_ptr body = m_actionMap[action]();

	if (body != nullptr)
	{
		body->SetNestingLevel(m_nestingLevel);
		bodies.insert(bodies.end(), body);
	}

	return true;
}

void CBodyFactory::SetPrintIndent(unsigned nestingLevel)
{
	m_nestingLevel = nestingLevel;
}

void CBodyFactory::SetDelimiters(char openDelimiter, char closeDelimiter)
{
	m_openDelimiter = openDelimiter;
	m_closeDelimiter = closeDelimiter;
}

bool CBodyFactory::IsOpenDelimiter(const string& line)
{
	size_t first = line.find_first_not_of(" ");
	return (first != string::npos) && (line[first] == m_openDelimiter);
}

bool CBodyFactory::IsCloseDelimiter(const string& line)
{
	size_t first = line.find_first_not_of(" ");
	return (first != string::npos) && (line[first] == m_closeDelimiter);
}