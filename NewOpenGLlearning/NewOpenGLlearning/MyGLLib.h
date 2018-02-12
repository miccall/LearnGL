#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm\glm.hpp>
#include <fstream>
#include <sstream>

using namespace std;
// settings
namespace miccall {

	//配置GLFw
	void ConfigGLFwWindow();

	//创建windows并返回
	GLFWwindow * InitGLFWwindow(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);

	//检查shader错误
	void CheckCompileErrors(int shader);

	void CheckCompileErrors(GLuint shader, std::string type);

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

	class Shader
	{
		public:
		// 程序ID
		unsigned int ID;

		// 构造器读取并构建着色器
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath );
		// 使用/激活程序
		void use();
		// uniform工具函数
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setVec2(const std::string & name, const glm::vec2 & value) const;
		void setVec2(const std::string & name, float x, float y) const;
		void setVec3(const std::string & name, const glm::vec3 & value) const;
		void setVec3(const std::string & name, float x, float y, float z) const;
		void setVec4(const std::string & name, const glm::vec4 & value) const;
		void setVec4(const std::string & name, float x, float y, float z, float w);
		void setMat2(const std::string & name, const glm::mat2 & mat) const;
		void setMat3(const std::string & name, const glm::mat3 & mat) const;
		void setMat4(const std::string & name, const glm::mat4 & mat) const;
	};
}