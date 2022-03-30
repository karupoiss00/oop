#include <cassert>
#include <sstream>
#include "BodyType.h"

using namespace std;

ostream& operator<<(ostream& os, const BodyType& bodyType)
{
	switch (bodyType)
	{
	case BodyType::Cylinder:
		os << "cylinder";
		break;
	case BodyType::Parallelepiped:
		os << "parallelepiped";
		break;
	case BodyType::Compound:
		os << "compound";
		break;
	case BodyType::Cone:
		os << "cone";
		break;
	case BodyType::Sphere:
		os << "sphere";
		break;
	default:
		assert(false);
	}

	return os;
}