#pragma once
#include "perlin.h"

class texture {
public:
	virtual Vec3 value(float u, float v, const Vec3& p) const = 0;
};

class constant_texture : public texture {
public:
	Vec3 color;
public:
	constant_texture() {}
	constant_texture(Vec3 c) : color(c) {}
	virtual Vec3 value(float u, float v, const Vec3& p) const {
		return color;
	}
};

class checker_texture : public texture {
public:
	texture *odd;
	texture *even;
public:
	checker_texture() {}
	checker_texture(texture *t0, texture *t1) : even(t0), odd(t1) { }
	virtual Vec3 value(float u, float v, const Vec3& p) const {
		float sines = sin(10 * p.x())*sin(10 * p.y())*sin(10 * p.z());
		if (sines < 0)
			return odd->value(u, v, p);
		else
			return even->value(u, v, p);
	}

};

class noise_texture : public texture {
public:
	perlin noise;
	float scale;
public:
	noise_texture() {}
	noise_texture(float sc) : scale(sc) {}
	virtual Vec3 value(float u, float v, const Vec3& p) const {
	    //         return Vec3(1,1,1)*0.5*(1 + noise.turb(scale * p));
		//            return Vec3(1,1,1)*noise.turb(scale * p);
		return Vec3(1, 1, 1)*0.5*(1 + sin(scale*p.z() + 10 * noise.turb(p)));
	}

};

class image_texture : public texture {
public:
	image_texture() {}
	image_texture(unsigned char *pixels, int A, int B) : data(pixels), nx(A), ny(B) {}
	virtual Vec3 value(float u, float v, const Vec3& p) const;
	unsigned char *data;
	int nx, ny;
};

Vec3 image_texture::value(float u, float v, const Vec3& p) const {
	int i = (u)*nx;
	int j = (1 - v)*ny - 0.001;
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i > nx - 1) i = nx - 1;
	if (j > ny - 1) j = ny - 1;
	float r = int(data[3 * i + 3 * nx*j]) / 255.0;
	float g = int(data[3 * i + 3 * nx*j + 1]) / 255.0;
	float b = int(data[3 * i + 3 * nx*j + 2]) / 255.0;
	return Vec3(r, g, b);
}

