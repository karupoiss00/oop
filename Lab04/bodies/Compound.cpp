#include <numeric>
#include "Compound.h"

using namespace std;

CCompound::CCompound()
	: CBody(BodyType::Compound) {}

bool CCompound::AddChildBody(const body_ptr& body)
{
	if (body->GetType() == BodyType::Compound)
	{
		return AddCompound(body);
	}

	if (body->GetParent() == nullptr)
	{
		CallSetParent(body.get(), this);
		m_bodies.push_back(body);

		return true;
	}

	return false;
}

bool CCompound::AddCompound(const body_ptr& body)
{
	CBody* addedBody = body.get();

	if (!addedBody || addedBody == this || addedBody->GetParent() != nullptr)
	{
		return false;
	}

	CBody* parent = GetParent();

	while (parent != nullptr)
	{

		if (parent == addedBody)
		{
			return false;
		}
		parent = parent->GetParent();
	}

	CallSetParent(addedBody, this);
	m_bodies.push_back(body);

	return true;
}

double CCompound::GetVolume() const
{
	return accumulate(m_bodies.begin(), m_bodies.end(), 0.0,
		[](double a, const body_ptr& body) {
		return a + body->GetVolume();
	});
}

double CCompound::GetMass() const
{
	return accumulate(m_bodies.begin(), m_bodies.end(), 0.0,
		[](double a, const body_ptr& body) {
		return a + body->GetMass();
	});
}

double CCompound::GetDensity() const
{
	double mass = GetMass();
	double volume = GetVolume();

	if (volume)
	{
		return mass / volume;
	}

	return 0;
}

void CCompound::AppendProperties(ostream& os) const
{
	os << string(m_nestingLevel + 2, ' ') << "{" << endl;

	for (size_t i = 0; i < m_bodies.size(); ++i)
	{
		os << m_bodies[i]->ToString();
	}

	os << string(m_nestingLevel + 2, ' ') << "}" << endl;
}