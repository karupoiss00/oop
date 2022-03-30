#define _USE_MATH_DEFINES
#include "BodyType.h"
#include "Cone.h"

using namespace std;

CCone::CCone(double density, double radius, double height)
	: CSolidBody(BodyType::Cone, density),
	  m_radius(radius),
	  m_height(height) {}

double CCone::GetRadius() const
{
	return m_radius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return (m_height * m_radius * m_radius * M_PI) / 3;
}

void CCone::AppendProperties(ostream& strm) const
{
	strm << string(m_nestingLevel + 2, ' ') << "radius = " << GetRadius() << endl;
	strm << string(m_nestingLevel + 2, ' ') << "height = " << GetHeight() << endl;
}