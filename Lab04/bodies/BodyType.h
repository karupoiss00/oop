#pragma once
#include <iostream>

enum class BodyType
{
	Sphere,
	Parallelepiped,
	Cone,
	Cylinder,
	Compound,
};

std::ostream& operator<<(std::ostream& os, const BodyType& bodyType);