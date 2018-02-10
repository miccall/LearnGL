#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
// settings
namespace miccall {

	//配置GLFw
	void ConfigGLFwWindow();

	//创建windows并返回
	GLFWwindow * InitGLFWwindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);

	//检查shader错误
	void CheckCompileErrors(int shader);

	//检查链接错误
	void CheckProgramErrors(int program);

	//连接shader 返回连接程序
	int LinkShader(int &vertex, int &frag);

	//
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//
	void processInput(GLFWwindow *window);

	//
	void CustomRender();
}