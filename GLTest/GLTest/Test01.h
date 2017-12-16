#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
using namespace std;


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// º¯ÊýÉùÃ÷  
// public 
int  Test01();
int  Test02();
int  Test03();
// private 
void ConfigGLFwWindow();
GLFWwindow * InitGLFWwindow();

void CheckCompileErrors(int shader);
void CheckProgramErrors(int program);
int LinkShader(int &vertext, int &frag);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void CustomRender();


