#pragma once

#include <fstream>
#include "sphere.h"
#include "hitablelist.h"
#include "material.h"
#include <glut.h>
#include <iostream>
#include "Camera.h"
#include <stdlib.h>
#include <thread>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "box.h"


hitable * two_sphere_mat_and_lam()
{
	int n = 50;
	hitable **list = new hitable*[n + 1];

	texture *sphere_tex = new constant_texture(Vec3(0.1, 0.2, 0.5));
	texture *earth_tex = new constant_texture(Vec3(0.8, 0.8, 0.0));
	material * sphere_mat = new lambertian(sphere_tex);
	material *earth_mat = new lambertian(earth_tex);
	material *metal_mat = new metal(Vec3(0.8, 0.6, 0.2), 0.3);

	list[0] = new moving_sphere(Vec3(0, 0, -1), Vec3(0, 0, -1) + Vec3(0, 0.5 + drand48(), 0), 0.0, 1.0, 0.5, sphere_mat);
	list[1] = new sphere(Vec3(0, -100.5, -1), 100, earth_mat);
	list[2] = new sphere(Vec3(1, 0, -1), 0.5, metal_mat);

	return new hitable_list(list, 3);

}

hitable * two_sphere()
{
	texture *checker = new checker_texture(new constant_texture(Vec3(0.2, 0.3, 0.1)), new constant_texture(Vec3(0.9, 0.9, 0.9)));
	int n = 50;
	hitable **list = new hitable*[n + 1];

	list[0] = new sphere(Vec3(0, -20, 0), 20, new lambertian(checker));
	list[1] = new sphere(Vec3(0, 20, 0), 20, new lambertian(checker));

	return new hitable_list(list, 2);
}

hitable *two_perlin_spheres() {
	texture *pertext = new noise_texture(2.5);
	hitable **list = new hitable*[2];
	list[0] = new sphere(Vec3(0, -1000, 0), 1000, new lambertian(pertext));
	list[1] = new sphere(Vec3(0, 2, 0), 2, new lambertian(pertext));
	return new hitable_list(list, 2);
}

hitable *earth() {
	int nx, ny, nn;
	//unsigned char *tex_data = stbi_load("tiled.jpg", &nx, &ny, &nn, 0);
	unsigned char *tex_data = stbi_load("cpj.jpg", &nx, &ny, &nn, 0);
	material *mat = new lambertian(new image_texture(tex_data, nx, ny));
	return new sphere(Vec3(0, 0, 0), 2, mat);
}

hitable *sample_light() {
	texture *pertext = new constant_texture(Vec3(0.5,0.5,0));
	hitable **list = new hitable*[5];
	list[0] = new sphere(Vec3(0, -10, 0), 10, new lambertian(pertext));
	//list[1] = new sphere(Vec3(0, 2, 0), 2, new lambertian(pertext));
	//list[2] = new sphere(Vec3(0, 7, 0), 2, new diffues_light(new constant_texture(Vec3(4, 4, 4))));
	list[1] = new xy_rect(3,5,1,3,-2, new diffues_light(new constant_texture(Vec3(4, 4, 4))));
	return new hitable_list(list, 2);
}


hitable *cornell_box() {
	hitable **list = new hitable*[6];
	int i = 0;
	material *red = new lambertian(new constant_texture(Vec3(0.65, 0.05, 0.05)));
	material *white = new lambertian(new constant_texture(Vec3(0.73, 0.73, 0.73)));
	material *green = new lambertian(new constant_texture(Vec3(0.12, 0.45, 0.15)));
	material *light = new diffues_light(new constant_texture(Vec3(15, 15, 15)));
	list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
	list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
	list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
	return new hitable_list(list, i);
}

hitable *cornell_box_two_rect() {

	hitable **list = new hitable*[8];
	int i = 0;
	
	material *red = new lambertian(new constant_texture(Vec3(0.65, 0.05, 0.05)));
	material *white = new lambertian(new constant_texture(Vec3(0.73, 0.73, 0.73)));
	material *green = new lambertian(new constant_texture(Vec3(0.12, 0.45, 0.15)));
	material *light = new diffues_light(new constant_texture(Vec3(4, 4, 4)));

	list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
	list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
	list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
	list[i++] = new translate( new rotate_y (new box(Vec3(0,0,0),Vec3(165,165,165),white),-18 ),Vec3(130,0,65));
	list[i++] = new translate(new rotate_y(new box(Vec3(0, 0, 0), Vec3(165, 330 , 165), white), 15), Vec3(265, 0, 295));

	return new hitable_list(list, i);
}