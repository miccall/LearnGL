#pragma once
struct hit_record;

#include "ray.h"
#include "hitable.h"
#include "texture.h"
#include "onb.h"

// 反射 
Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n)*n;
}

// 折射 
bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) {
	Vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);
	if (discriminant > 0) {
		refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
		return true;
	}
	else
		return false;
}


float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0*r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}

class material {
public:
	// old interface 
	virtual bool scatter(const Ray & r_in, const hit_record& rec, Vec3 & attenuation, Ray & scatterd) const = 0;

	// new 
	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3 & albedo , Ray& scattered , float &pdf ) const
	{
		return false;
	};
	
	// with MC function 
	virtual float scattering_pdf(const Ray& r_in, const hit_record& rec, const Ray& scattered) const
	{
		return false ;
	};
	
	virtual Vec3 emitted(float u, float v, const Vec3 & p) const {
		return Vec3(0, 0, 0);
	}
};

class metal : public material
{
public:
	Vec3 albedo;
	float fuzz;
public:
	metal(const Vec3 & a , float f ) : albedo(a),fuzz(f) {}
	virtual bool scatter(const Ray & r_in, const hit_record& rec, Vec3 & attenuation, Ray & scatterd) const {
		Vec3 reflected = reflect(unit_vector(r_in.Direction()), rec.normal);
		scatterd = Ray(rec.p, reflected + fuzz * Random_in_unitt_cube());
		attenuation = albedo;
		return (dot(scatterd.Direction(), rec.normal) > 0);
	}
};

class lambertian : public material
{
public:
	texture *albedo;
public:
	lambertian(texture* a) : albedo(a) {}

	virtual float scattering_pdf(const Ray& r_in, const hit_record& rec, const Ray& scattered) const {
		float cosine = dot(rec.normal, unit_vector(scattered.Direction()));
		if (cosine < 0) 
			cosine = 0;
		return cosine / M_PI ;
	}

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3 & alb, Ray& scattered, float &pdf) const {
		/*Vec3 target = rec.p + rec.normal + Random_in_unitt_cube();
		scattered = Ray(rec.p, unit_vector(target - rec.p), r_in.time());
		*/
		/*
		Vec3 direction;
		do
		{
			direction = Random_in_unitt_cube();
		} while (dot(direction , rec.normal ) < 0 );
		*/
		onb uvw;
		uvw.build_from_w(rec.normal);
		Vec3 direction = uvw.local( Random_cosine_direction() );
		scattered = Ray(rec.p,  unit_vector( direction ) , r_in.time());
		alb = albedo->value(rec.u, rec.v, rec.p);
		pdf = dot(uvw.w(), scattered.Direction()) / M_PI;
		return true;
	}

	virtual bool scatter(const Ray & r_in , const hit_record& rec , Vec3 & attenuation , Ray & scatterd ) const {

		Vec3 target = rec.p + rec.normal + Random_in_unitt_cube() ;
		scatterd = Ray(rec.p, target - rec.p , r_in.time());
		attenuation = albedo->value(0,0,rec.p);
		return true;
	}
};

class dielectric : public material {
public:
	float ref_idx;
public:
	dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const {
		Vec3 outward_normal;
		Vec3 reflected = reflect(r_in.Direction(), rec.normal);
		float ni_over_nt;
		attenuation = Vec3(1.0, 1.0, 1.0);
		Vec3 refracted;
		float reflect_prob;
		float cosine;
		if (dot(r_in.Direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = dot(r_in.Direction(), rec.normal) / r_in.Direction().length();
			cosine = sqrt(1 - ref_idx*ref_idx*(1 - cosine*cosine));
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.Direction(), rec.normal) / r_in.Direction().length();
		}
		if (refract(r_in.Direction(), outward_normal, ni_over_nt, refracted))
			reflect_prob = schlick(cosine, ref_idx);
		else
			reflect_prob = 1.0;
		if (drand48() < reflect_prob)
			scattered = Ray(rec.p, reflected);
		else
			scattered = Ray(rec.p, refracted);
		return true;
	}
};


class diffues_light : public material 
{
public:
	texture *emit;
public:
	diffues_light( texture * a ) : emit(a) {};

	virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const {
		return false;
	}
	virtual Vec3 emitted(float u, float v, const Vec3 & p) const {
		return emit->value(u, v, p);
	}
};
