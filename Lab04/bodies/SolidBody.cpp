#include "SolidBody.h"

CSolidBody::CSolidBody(BodyType type, double density)
	: CBody(type), m_density(density) {}

CSolidBody::~CSolidBody() {}

double CSolidBody::GetDensity() const
{
	return m_density;
}

double CSolidBody::GetMass() const
{
	return GetVolume() * GetDensity();
}