#define _USE_MATH_DEFINES
#include "Cylinder.h"
#include "BodyType.h"

using namespace std;

CCylinder::CCylinder(double density, double radius, double height)
	: CSolidBody(BodyType::Cylinder, density), m_radius(radius), m_height(height) {}

double CCylinder::GetRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return m_height * m_radius * m_radius * M_PI;
}

void CCylinder::AppendProperties(ostream& os) const
{
	os << string(m_nestingLevel + 2, ' ') << "radius = " << GetRadius() << endl;
	os << string(m_nestingLevel + 2, ' ') << "height = " << GetHeight() << endl;
}