#include "Test01.h"
#include "Shader.h"
#include "vector"
#pragma once
/*
绑定VAO和VBO对象 ，并且把数据传递到VBO缓存中。
VAO对象指针 ，VBO对象指针 ， 数据数组 ，数据类型长度 
*/
template<typename T>
void Blind_VAO_VBO(unsigned int * VAO, unsigned int * VBO, T *vec, int lenght);

template<typename T>
void Blind_VAO_VBO(unsigned int * VAO , unsigned int * VBO,T *vec, int lenght )
{
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, lenght * sizeof(vec), vec, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void GPU_setColor(float R ,float G,float B ,float A)
{
	glClearColor(R,G,B,A);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool isRenderWindow(GLFWwindow * window)
{
	return !glfwWindowShouldClose(window);
}

void GPU_close(unsigned int * VAO, unsigned int * VBO) 
{
	glDeleteVertexArrays(1, VAO);
	glDeleteBuffers(1, VBO);
	glfwTerminate();
}
