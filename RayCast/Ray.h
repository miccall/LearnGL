#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray();
	Ray(const Vec3 & a , const Vec3 & b );
	Ray(const Vec3 & a, const Vec3 & b, float ti);
	Vec3 Origin() const;
	Vec3 Direction() const; 
	float time() const;
	Vec3 point_at_parameter(float t) const;

	Vec3 A;
	Vec3 B;
	float _time;
};

//默认构造函数 
Ray::Ray() {}

// 构造函数 ： a ：光线原点 ， b ： 光线方向 
Ray::Ray(const Vec3 & a, const Vec3 & b)
{
	A = a;
	B = b;
	_time = 0.0;
}

Ray::Ray(const Vec3 & a, const Vec3 & b, float ti)
{
		A = a;
		B = b;
		_time = ti;
}

Vec3 Ray::Origin() const
{
	return A;
}

float Ray::time()const
{
	return _time;
}

Vec3 Ray::Direction() const
{
	return B;
}

Vec3 Ray::point_at_parameter(float t) const
{
	return  A + t * B;
}

