#include "BodyType.h"
#include "Parallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
	: CSolidBody(BodyType::Parallelepiped, density),
	  m_width(width),
	  m_height(height),
	  m_depth(depth) {}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}

void CParallelepiped::AppendProperties(ostream& os) const
{
	os << string(m_nestingLevel + 2, ' ') << "width = " << GetWidth() << endl;
	os << string(m_nestingLevel + 2, ' ') << "height = " << GetHeight() << endl;
	os << string(m_nestingLevel + 2, ' ') << "depth = " << GetDepth() << endl;
}