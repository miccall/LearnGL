#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray();
	Ray(const Vec3 & a , const Vec3 & b );
	Vec3 Origin() const;
	Vec3 Direction() const; 
	Vec3 point_at_parameter(float t) const;

	Vec3 A;
	Vec3 B;
};
