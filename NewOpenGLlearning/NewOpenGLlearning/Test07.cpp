#include "MyCourses.h"

/*
* 使用从文件加载的Shader
*/
int Test07()
{
	ConfigGLFwWindow();
	GLFWwindow * window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == nullptr)
	{
		return -1;
	}
	Shader ourShader("Shader01.vs","Shader01.fs",nullptr);
	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/**
	*  glVertexAttribPointer
	*  第一个参数是传入着色器中的 location 值
	*  第二个参数是指定数据类型 Vec3 =>  3
	*  第三，第四参数是值类型 FLOAT 和 是否希望数据被标准化 FALSE
	*  第五个参数是步长(Stride) ， 第一个数据到第二个相同属性数据的间距 。（一个点包含所有信息的总单位）
	*  第六个参数 是 位置数据在缓冲中起始位置的偏移量。也就是这个数据起始的位置到开头的距离 。
	*/

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		CustomRender();
		ourShader.use();
		// glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		// 绘制顶点个数 ，偏移 
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}