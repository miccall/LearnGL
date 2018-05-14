#pragma once

#include "AxisAlignedBoundBox.h"
#include <float.h>

class material;

void get_sphere_uv(const Vec3& p, float& u, float& v) {
	float phi = atan2(p.z(), p.x());
	float theta = asin(p.y());
	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}

struct hit_record
{
	float t;
	float u;
	float v;
	Vec3 p;
	Vec3 normal;
	material * mat_ptr;
};

class hitable {
public:
	virtual bool hit(const Ray & r, float t_min, float t_max, hit_record & rec) const = 0;
	virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
};


class flip_normals : public hitable {
public:
	flip_normals(hitable *p) : ptr(p) {}
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
		if (ptr->hit(r, t_min, t_max, rec)) {
			rec.normal = -rec.normal;
			return true;
		}
		else
			return false;
	}
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		return ptr->bounding_box(t0, t1, box);
	}
	hitable *ptr;
};


class translate : public hitable {
public:
	translate(hitable *p, const Vec3& displacement) : ptr(p), offset(displacement) {}
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const;
	hitable *ptr;
	Vec3 offset;
};

bool translate::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
	Ray moved_r(r.Origin() - offset, r.Direction(), r.time());
	if (ptr->hit(moved_r, t_min, t_max, rec)) {
		rec.p += offset;
		return true;
	}
	else
		return false;
}

bool translate::bounding_box(float t0, float t1, aabb& box) const {
	if (ptr->bounding_box(t0, t1, box)) {
		box = aabb(box.min() + offset, box.max() + offset);
		return true;
	}
	else
		return false;
}

class rotate_y : public hitable {
public:
	rotate_y(hitable *p, float angle);
	virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, aabb& box) const {
		box = bbox; return hasbox;
	}
	hitable *ptr;
	float sin_theta;
	float cos_theta;
	bool hasbox;
	aabb bbox;
};

rotate_y::rotate_y(hitable *p, float angle) : ptr(p) {
	float radians = (M_PI / 180.) * angle;
	sin_theta = sin(radians);
	cos_theta = cos(radians);
	hasbox = ptr->bounding_box(0, 1, bbox);
	Vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	Vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				float x = i*bbox.max().x() + (1 - i)*bbox.min().x();
				float y = j*bbox.max().y() + (1 - j)*bbox.min().y();
				float z = k*bbox.max().z() + (1 - k)*bbox.min().z();
				float newx = cos_theta*x + sin_theta*z;
				float newz = -sin_theta*x + cos_theta*z;
				Vec3 tester(newx, y, newz);
				for (int c = 0; c < 3; c++)
				{
					if (tester[c] > max[c])
						max[c] = tester[c];
					if (tester[c] < min[c])
						min[c] = tester[c];
				}
			}
		}
	}
	bbox = aabb(min, max);
}

bool rotate_y::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {
	Vec3 origin = r.Origin();
	Vec3 direction = r.Direction();
	origin[0] = cos_theta*r.Origin()[0] - sin_theta*r.Origin()[2];
	origin[2] = sin_theta*r.Origin()[0] + cos_theta*r.Origin()[2];
	direction[0] = cos_theta*r.Direction()[0] - sin_theta*r.Direction()[2];
	direction[2] = sin_theta*r.Direction()[0] + cos_theta*r.Direction()[2];
	Ray rotated_r(origin, direction, r.time());
	if (ptr->hit(rotated_r, t_min, t_max, rec)) {
		Vec3 p = rec.p;
		Vec3 normal = rec.normal;
		p[0] = cos_theta*rec.p[0] + sin_theta*rec.p[2];
		p[2] = -sin_theta*rec.p[0] + cos_theta*rec.p[2];
		normal[0] = cos_theta*rec.normal[0] + sin_theta*rec.normal[2];
		normal[2] = -sin_theta*rec.normal[0] + cos_theta*rec.normal[2];
		rec.p = p;
		rec.normal = normal;
		return true;
	}
	else
		return false;
}