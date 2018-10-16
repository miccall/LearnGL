#include "MyCourses.h"
/*
	assimp :
*/

int Test27()
{
	// glfw 窗口管理 opengl 
	ConfigGLFwWindow();
	GLFWwindow *window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == nullptr) return -1;
	
	// 开启深度缓冲
	glEnable(GL_DEPTH_TEST);

	// 着色器和模型：
	Shader ourShader("Shader27.vs", "Shader27.fs", nullptr);
	Model ourModel("model/nanosuit.obj");

	// 渲染循环 
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		CustomRender();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		// GL_DEPTH_BUFFER_BIT ： 开启深度测试之后，用这个来清除深度缓冲，否则你会仍在使用上一次渲染迭代中的写入的深度值：
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		
		glm::mat4 projection = projectionMatrix();
		glm::mat4 view = viewMatrix();
		glm::mat4 model;

			model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down


		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		ourShader.setMat4("model", model);
		
		ourModel.Draw(ourShader);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}
