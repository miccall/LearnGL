#pragma once
#include "Scene.h"

std::ofstream outf;

// data of image 
const GLint  ImageWidth = 400;
const GLint  ImageHeight = 400;
GLint    PixelLength;
GLbyte * PixelData;
const GLint SamplingRate = 1000;
const GLint rgbwidth = ImageWidth * 3;
Vec3* col;
int count = 2;
Vec3 colorvec;


// data of cam 
Vec3 lookfrom = Vec3(278, 278, -800);
Vec3 lookat = Vec3(278, 278, 0);

/*
Vec3 lookfrom = Vec3(13, 2, 3);
Vec3 lookat = Vec3(0,0, 0);
*/

// 焦距 
float dist_to_foucus = 10;

// 光圈大小 
float aperture = 0;

// data of world => scene :
hitable *world = cornell_box_two_rect();

Camera cam(lookfrom, lookat, Vec3(0, 1, 0), 40, float(ImageWidth) / float(ImageHeight), aperture, dist_to_foucus);