#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// settings
namespace miccall {

	// camera
	extern glm::vec3 cameraPos ;
	extern glm::vec3 cameraFront;
	extern glm::vec3 cameraUp ;

	// timing
	extern float deltaTime ;	// time between current frame and last frame
	extern float lastFrame ;


	extern bool firstMouse ;
	extern float yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	extern float pitch ;
	extern float lastX ;
	extern float lastY ;
	extern float fov ;
	extern unsigned int SCR_WIDTH;
	extern unsigned int SCR_HEIGHT;

	extern enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
	// Default camera values
	extern const float YAW ;
	extern const float PITCH ;
	extern const float SPEED ;
	extern const float SENSITIVTY;
	extern const float ZOOM ;

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

	//处理输入 
	void processInput(GLFWwindow *window);

	//渲染预处理
	void CustomRender();

	//鼠标滚轮和移动的事件 
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//生成纹理
	unsigned int creatTexture(const char * filename);

	glm::mat4 projectionMatrix();
	glm::mat4 viewMatrix();
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

	class Camera {
	public:
		// Camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// Eular Angles
		float Yaw;
		float Pitch;
		// Camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		// Constructor with vectors
		//Camera(glm::vec3 position , glm::vec3 up, float yaw, float pitch);
		Camera();
		Camera(glm::vec3 position , glm::vec3 up, float yaw , float pitch);
		// Constructor with scalar values
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

		// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
		glm::mat4 GetViewMatrix();

		// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
		void ProcessKeyboard(Camera_Movement direction, float deltaTime);

		// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch );

		// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
		void ProcessMouseScroll(float yoffset);
	private:
		// Calculates the front vector from the Camera's (updated) Eular Angles
		void updateCameraVectors();
	};


	extern Camera camera;
}