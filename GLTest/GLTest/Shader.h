#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>
class Shader
{
public:
	// ����ID
	unsigned int ID;
	// ��������ȡ��������ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// ʹ��/�������
	void use();
	// uniform���ߺ���
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

#endif