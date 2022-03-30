#pragma once
#include "Solidbody.h"

class CParallelepiped : public CSolidBody
{
public:
	CParallelepiped(double density, double width, double height, double depth);

	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;

	double GetVolume() const override;

protected:
	void AppendProperties(std::ostream& os) const override;

private:
	double m_width;
	double m_height;
	double m_depth;
};