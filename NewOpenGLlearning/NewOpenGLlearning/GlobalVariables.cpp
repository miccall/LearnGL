#include "MyGLLib.h"

namespace miccall{
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;

	// camera
	
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;


	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = SCR_WIDTH / 2.0;
	float lastY = SCR_HEIGHT / 2.0;
	float fov = 45.0f;


	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVTY = 0.1f;
	const float ZOOM = 45.0f;
	const glm::vec3 worldup = glm::vec3(0.0f, 1.0f, 0.0f); 
	// 位置 ， up ， 左右旋转 ，上下旋转 。
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), worldup, YAW , PITCH );
}