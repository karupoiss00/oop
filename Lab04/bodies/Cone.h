#pragma once
#include "Solidbody.h"

class CCone : public CSolidBody
{
public:
	CCone(double density, double radius, double height);

	double GetRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	double m_radius;
	double m_height;
};