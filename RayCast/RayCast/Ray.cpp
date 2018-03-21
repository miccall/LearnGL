#include "Ray.h"

Ray::Ray()
{
}
Ray::Ray(const Vec3 & a, const Vec3 & b)
{
	A = a;
	B = b;
}
Vec3 Ray::Origin() const
{
	return A;
}

Vec3 Ray::Direction() const
{
	return B;
}

Vec3 Ray::point_at_parameter(float t) const
{
	return  A + t * B;
}