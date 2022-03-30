#pragma once
#include "BodyType.h"
#include "Body.h"

class CSolidBody : public CBody
{
public:
	CSolidBody(BodyType type, double density);

	double GetDensity() const override;
	double GetMass() const override;

	virtual ~CSolidBody();

private:
	double m_density;
};
