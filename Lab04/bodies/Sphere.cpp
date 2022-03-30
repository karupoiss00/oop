#define _USE_MATH_DEFINES
#include "BodyType.h"
#include "Sphere.h"

using namespace std;

CSphere::CSphere(double density, double radius)
	: CSolidBody(BodyType::Sphere, density), m_radius(radius) {}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (pow(m_radius, 3) * M_PI) * 4 / 3;
}

void CSphere::AppendProperties(ostream& os) const
{
	os << string(m_nestingLevel + 2, ' ') << "radius = " << GetRadius() << endl;
}