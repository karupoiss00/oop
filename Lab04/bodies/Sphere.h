#pragma once
#include "Solidbody.h"

class CSphere : public CSolidBody
{
public:
	CSphere(double density, double radius);

	double GetRadius() const;
	double GetVolume() const override;

protected:
	void AppendProperties(std::ostream& os) const override;

private:
	double m_radius;
};
