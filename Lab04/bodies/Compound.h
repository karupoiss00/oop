#pragma once
#include "Body.h"

class CCompound : public CBody
{
public:
	CCompound();

	double GetVolume() const override;
	double GetDensity() const override;
	double GetMass() const override;

	bool AddChildBody(const body_ptr& body);

protected:
	void AppendProperties(std::ostream& os) const override;
	bool AddCompound(const body_ptr& body);

private:
	Bodies m_bodies;
};
