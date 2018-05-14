#pragma once
#include "hitable.h"

class sphere : public hitable
{
public:
	Vec3 center;
	float Radius;
	material *mat_ptr;
public:
	sphere() {};
	sphere(Vec3 cen, float r , material * m ) : center(cen), Radius(r),mat_ptr(m) {}
	virtual bool hit(const Ray & r , float tmin , float tmax , hit_record & rec ) const ;
	virtual bool bounding_box(float t0, float t1, aabb& box) const;
};

bool sphere::bounding_box(float t0, float t1, aabb& box) const {
	box = aabb(center - Vec3(Radius, Radius, Radius), center + Vec3(Radius, Radius, Radius));
	return true;
}

class moving_sphere:public hitable
{

public:
	Vec3 center0,center1 ;
	float time0, time1;
	float radius;
	material * mat_ptr;

public:
	moving_sphere() {};
	moving_sphere(Vec3  cen0 , Vec3 cen1 , float t0 , float t1 ,float r , material * m ):center0(cen0) , center1(cen1),time0(t0) , time1(t1) ,radius(r),mat_ptr(m){};

	virtual bool hit(const Ray & r, float tmin, float tmax, hit_record & rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const;
	Vec3 center(float time) const;

};

bool moving_sphere::hit(const Ray & r, float tmin, float tmax, hit_record & rec) const
{
	Vec3 oc = r.Origin() - center(r.time());

	float a = dot(r.Direction(), r.Direction());
	float b = dot(oc, r.Direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / (a);
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(b*b - a*c)) / (a);
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

Vec3 moving_sphere::center(float time) const {
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}


bool moving_sphere::bounding_box(float t0, float t1, aabb& box) const {
	aabb box0(center(t0) - Vec3(radius, radius, radius), center(t0) + Vec3(radius, radius, radius));
	aabb box1(center(t1) - Vec3(radius, radius, radius), center(t1) + Vec3(radius, radius, radius));
	box = surrounding_box(box0, box1);
	return true;
}


bool sphere::hit(const Ray & r, float tmin, float tmax, hit_record & rec) const
{
	Vec3 oc = r.Origin() - center;
	float a = dot(r.Direction(), r.Direction());
	float b = dot(oc, r.Direction());
	float c = dot(oc, oc) - Radius * Radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b*b - a*c)) / (a) ;
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			get_sphere_uv((rec.p - center) / Radius, rec.u, rec.v);
			rec.normal = (rec.p - center) / Radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(b*b - a*c)) / ( a);
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			get_sphere_uv((rec.p - center) / Radius, rec.u, rec.v);
			rec.normal = (rec.p - center) / Radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}
