#include <fstream>
#include "sphere.h"
#include "hitablelist.h"
#include <glut.h>
#include <iostream>
#include "Camera.h"
#include <stdlib.h>

static unsigned long long seed = 1;
const GLint  ImageWidth = 200;
const GLint  ImageHeight = 100;
GLint     PixelLength;
GLbyte * PixelData;
const GLint SamplingRate = 100;

// 随机数 
float drand48()
{
	const long long  m = 0x100000000LL , ra  = 0x5DEECE66DLL ;
	int rc = 0xB16;
	seed = (ra * seed + rc) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return (float) ((double)x / (double)m);
}

// 随机反射点 
Vec3 Random_in_unitt_cube()
{
	Vec3 p;
	do
	{
		p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1,1,1);

	} while (p.squared_length() >= 1.0 );
	return p;
}

// openGL 初始化 
void init(int argc, char** argv,unsigned int mode, int x_position, int y_position, int width, int heigth,const char * title )
{
	// GL 初始化 
	glutInit(&argc, argv);
	// 开启双缓冲机制 和 颜色缓冲 
	glutInitDisplayMode(mode);
	// 窗口位置 
	glutInitWindowPosition(x_position, y_position);
	// 窗口尺寸
	glutInitWindowSize(width, heigth);
	// 窗口名称 
	glutCreateWindow(title);

	// 清空颜色缓存 
	glClearColor(1.0, 0.0, 1.0, 1.0);
	// 矩阵模式 
	/*
	GL_MODELVIEW： 应用这个参数后，表示接下来的矩阵操作都是针对模型视景矩阵堆栈 。  直到下一次调用这个函数并更改参数为止。
	GL_PROJECTION：应用这个参数后，表示接下来的矩阵操作都是针对投影矩阵堆栈    。  直到下一次调用这个函数并更改参数为止。
	GL_TEXTURE ：  应用这个参数后，表示接下来的矩阵操作都是针对纹理矩阵堆栈    。  直到下一次调用这个函数并更改参数为止。
	*/
	glMatrixMode(GL_PROJECTION);
	//特殊的正射投影函数 left right bottom top 
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

// 是否击中一个球 (废弃方法)
bool ishit_sphere(const Vec3 & center, float Radius, const Ray & r)
{
	Vec3 oc = r.Origin() - center;
	float a = dot(r.Direction(), r.Direction());
	float b = 2.0 * dot(oc, r.Direction());
	float c = dot(oc, oc) - Radius * Radius;
	float discriminant = b* b - 4 * a * c;
	return (discriminant > 0);
}

// 返回 击中球时的 t 
float hit_sphere(const Vec3 & center, float Radius, const Ray & r)
{
	Vec3 oc = r.Origin() - center;
	float a = dot(r.Direction(), r.Direction());
	float b = 2.0 * dot(oc, r.Direction());
	float c = dot(oc, oc) - Radius * Radius;
	float discriminant = b* b - 4 * a * c;
	if (discriminant < 0)
		return -1;
	else
		return (-b - sqrt(discriminant)) / (2.0 * a);
}

// 光线击中的颜色 
Vec3 color(const Ray& r)
{
	Vec3 sphereorgin(0,0,-1);
	/* 射线画一个圆 
	if (ishit_sphere(Vec3(0, 0, -1), 0.5, r))
		return Vec3(1.0, 0.0, 0.0);
	*/
	float t = hit_sphere(sphereorgin, 0.5, r);
	if (t > 0.0) 
	{
		// object normal 
		Vec3 N = unit_vector(r.point_at_parameter(t) - sphereorgin );
		return 0.5 * Vec3(N.x()+1 , N.y()+1 ,N.z()+1 );
	}

	Vec3 unit_direction = unit_vector(r.Direction());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

// 光线击中的颜色
Vec3 color(const Ray& r, hitable * world)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		Vec3 target = rec.p + rec.normal + Random_in_unitt_cube();
		return 0.5 * color(Ray(rec.p, target - rec.p), world);
		// return 0.5 * Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		Vec3 unit_direction = unit_vector(r.Direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}

// 伽马矫正 
Vec3 Gamma_Correct(Vec3 col)
{
	float gammafactor = float(SamplingRate);
	col /= gammafactor ;
	return Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
}

// 显示进度
void showProgress(int num , int sum )
{
	system("cls");
	std::cout << (sum - num) * 100 / sum << "%" << std::endl;
}

// 数据计算加载 
void data()
{
	// 计算像素数据长度
	PixelLength = ImageWidth * 3;
	while (PixelLength % 3 != 0)
		++PixelLength;
	PixelLength *= ImageHeight;

	hitable *list[2];
	list[0] = new sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new sphere(Vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);

	Camera cam;

	const GLint rgbwidth = ImageWidth * 3;
	PixelData = new GLbyte [PixelLength];

	for (int j = ImageHeight - 1 ; j >= 0; j--)
	{
		showProgress(j,ImageHeight);
		for (int i = 0 , k = 0 ; i < rgbwidth; i+=3, k++ )
		{
			Vec3 col(0, 0, 0);
			for (int s = 0; s < SamplingRate ; s++)
			{
				float u = float(k + drand48()) / float(ImageWidth);
				float v = float(j + drand48()) / float(ImageHeight);

				Ray r = cam.getRay(u, v);
				Vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			//col /= float(SamplingRate);
			col = Gamma_Correct(col);
			// 像素数据 
			PixelData[ j *(rgbwidth)+(i + 0 )] = (GLbyte) int(255.99 * col[0]);  // R
			PixelData[ j *(rgbwidth)+(i + 1 )] = (GLbyte) int(255.99 * col[1]);  // G
			PixelData[ j *(rgbwidth)+(i + 2 )] = (GLbyte) int(255.99 * col[2]);  // B

		}
	}
}

// 保存渲染图片 
void savepic()
{
	//文件访问
	std::ofstream outf;
	outf.open("C:/Users/miccall/Desktop/abc.ppm");
	outf << "P3\n" << ImageWidth << " " << ImageHeight << "\n255\n";
	for (int i = 0; i < PixelLength; i++)
	{
		outf << PixelData[i] << " ";
		if (i % 3 == 0)
			outf << "\n";
	}
	outf.close();
	std::cout << "finished" << std::endl;
}

//opengl着色 
void pixel()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(ImageWidth, ImageHeight,
		GL_RGB, GL_UNSIGNED_BYTE, PixelData);

	glutSwapBuffers();
}

// 主方法 
int main(int argc, char** argv)
{
	data();
	// GL 初始化 自定义初始化内容
	init(argc, argv, GLUT_DOUBLE | GLUT_RGBA, 100, 100, ImageWidth, ImageHeight, "miccall");
	glutDisplayFunc(pixel);
	glutMainLoop();
	return 0;
}
