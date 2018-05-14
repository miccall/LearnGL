#pragma once
#include "Config.h"

// 光线击中的颜色
Vec3 color(const Ray& r, hitable * world, int depth)
{
	hit_record rec;
	if ( world->hit(r, 0.001, FLT_MAX, rec))
	{
		Ray scattered;
		Vec3 attenuation;
		Vec3 albedo;
		float pdf;
		Vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		if (depth < 50 && rec.mat_ptr->scatter(r, rec,albedo,scattered,pdf))
		{
			return emitted + albedo*rec.mat_ptr->scattering_pdf(r,rec,scattered) * color(scattered, world, depth + 1) / pdf ; 
		}
		else
		{
			return emitted;
			//return Vec3(1, 1, 1);
		}

	}
	else
	{
		/*
		backgroud 

		Vec3 unit_direction = unit_vector(r.Direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);

		*/

		return Vec3(0, 0, 0);
	}
}


// 伽马矫正 
Vec3 Gamma_Correct(Vec3 col)
{
	return Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
}

/*
Vec3 color(const Ray& r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		Ray scattered;
		Vec3 attenuation;
		Vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return emitted + attenuation*color(scattered, world, depth + 1);
		else
			return emitted;
	}
	else
		return Vec3(0, 0, 0);
}
*/

