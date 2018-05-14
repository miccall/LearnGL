#pragma once

#include "hitable.h"
class xy_rect : public hitable
{
public:
	xy_rect() { } ;
	xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *mat) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};
	virtual bool hit(const Ray& r, float t0, float t1, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		box = aabb(Vec3(x0, y0, k - 0.0001), Vec3(x1, y1, k + 0.0001));
		return true;
	}
	material  *mp;
	float x0, x1, y0, y1, k;
};

bool xy_rect::hit(const Ray& r, float t0, float t1, hit_record& rec) const {
	float t = (k - r.Origin().z()) / r.Direction().z();
	if (t < t0 || t > t1)
		return false;
	float x = r.Origin().x() + t*r.Direction().x();
	float y = r.Origin().y() + t*r.Direction().y();
	if (x < x0 || x > x1 || y < y0 || y > y1)
		return false;
	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = Vec3(0, 0, 1);
	return true;
}

class xz_rect : public hitable {
public:
	xz_rect() {}
	xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {};
	virtual bool hit(const Ray& r, float t0, float t1, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		box = aabb(Vec3(x0, k - 0.0001, z0), Vec3(x1, k + 0.0001, z1));
		return true;
	}
	material  *mp;
	float x0, x1, z0, z1, k;
};

class yz_rect : public hitable {
public:
	yz_rect() {}
	yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {};
	virtual bool hit(const Ray& r, float t0, float t1, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		box = aabb(Vec3(k - 0.0001, y0, z0), Vec3(k + 0.0001, y1, z1));
		return true;
	}
	material  *mp;
	float y0, y1, z0, z1, k;
};

bool xz_rect::hit(const Ray& r, float t0, float t1, hit_record& rec) const {
	float t = (k - r.Origin().y()) / r.Direction().y();
	if (t < t0 || t > t1)
		return false;
	float x = r.Origin().x() + t*r.Direction().x();
	float z = r.Origin().z() + t*r.Direction().z();
	if (x < x0 || x > x1 || z < z0 || z > z1)
		return false;
	rec.u = (x - x0) / (x1 - x0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = Vec3(0, 1, 0);
	return true;
}

bool yz_rect::hit(const Ray& r, float t0, float t1, hit_record& rec) const {
	float t = (k - r.Origin().x()) / r.Direction().x();
	if (t < t0 || t > t1)
		return false;
	float y = r.Origin().y() + t*r.Direction().y();
	float z = r.Origin().z() + t*r.Direction().z();
	if (y < y0 || y > y1 || z < z0 || z > z1)
		return false;
	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	rec.mat_ptr = mp;
	rec.p = r.point_at_parameter(t);
	rec.normal = Vec3(1, 0, 0);
	return true;
}