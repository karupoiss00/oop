#pragma once
#include <string>
#include <vector>
#include "BodyType.h"

class CBody
{
public:
	CBody(BodyType type);

	virtual double GetDensity() const = 0;
	virtual double GetVolume() const = 0;
	virtual double GetMass() const = 0;
	
	BodyType GetType() const;
	void SetNestingLevel(unsigned nestingLevel);
	std::string ToString() const;

	CBody* GetParent() const;

	bool operator== (const CBody& body) const;
	virtual ~CBody();

protected:
	static void CallSetParent(CBody* target, CBody* parent);
	void SetParent(CBody* parent);
	virtual void AppendProperties(std::ostream& os) const = 0;

	unsigned m_nestingLevel;

private:
	BodyType m_type;
	CBody* m_parent;
};

using body_ptr = std::shared_ptr<CBody>;
using Bodies = std::vector<body_ptr>;