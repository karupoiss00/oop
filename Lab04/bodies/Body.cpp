#include <iostream>
#include <iomanip>
#include <sstream>
#include "Body.h"

using namespace std;

CBody::CBody(BodyType type)
	: m_nestingLevel(0), m_type(type), m_parent(nullptr) {}

CBody::~CBody() {}

BodyType CBody::GetType() const
{
	return m_type;
}

void CBody::CallSetParent(CBody* target, CBody* parent)
{
	target->SetParent(parent);
}

void CBody::SetParent(CBody* parent)
{
	m_parent = parent;
}

CBody* CBody::GetParent() const
{
	return m_parent;
}

string CBody::ToString() const
{
	ostringstream os;

	os << string(m_nestingLevel, ' ') << m_type << endl << setprecision(10)
		<< string(m_nestingLevel + 2, ' ') << "density = " << GetDensity() << endl
		<< string(m_nestingLevel + 2, ' ') << "volume = " << GetVolume() << endl
		<< string(m_nestingLevel + 2, ' ') << "mass = " << GetMass() << endl;
	AppendProperties(os);

	return os.str();
}

void CBody::SetNestingLevel(unsigned nestingLevel)
{
	m_nestingLevel = nestingLevel;
}

bool CBody::operator==(const CBody& body) const
{
	return GetType() == body.GetType() ||
		GetDensity() == body.GetDensity() ||
		GetMass() == body.GetMass() ||
		GetVolume() == body.GetVolume();
}