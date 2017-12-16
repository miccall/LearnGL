#include "MyGUP.h"

// 从文件加载shader 
int Test03()
{
	ConfigGLFwWindow();
	GLFWwindow * window = InitGLFWwindow();
	//加载shader文件 
	Shader ourShader("vert.vs", "frag.fs");
	
	float vertices[] = {
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};

	unsigned int VBO, VAO;
	Blind_VAO_VBO( &VAO,&VBO,vertices, sizeof( vertices) / sizeof( vertices[0] ));

	//渲染循环 
	while (isRenderWindow(window))
	{
		processInput(window);
		GPU_setColor(0.2f, 0.3f, 0.3f, 1.0f);
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	GPU_close(&VAO,&VBO);
	return 0;
}