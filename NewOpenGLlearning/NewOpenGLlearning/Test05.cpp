#include "MyCourses.h"

/*
*  着色器的使用
*/
int Test05()
{
	const char *vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";

	miccall::ConfigGLFwWindow();
	GLFWwindow * window = miccall::InitGLFWwindow(SCR_WIDTH,SCR_HEIGHT);
	if (window == nullptr)
		return -1;

	int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexshader);
	CheckCompileErrors(vertexshader);

	int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);
	CheckCompileErrors(fragmentshader);
	int shaderprogram = LinkShader(vertexshader, fragmentshader);


	float vertices[] = {
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f   // top 
	};

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 如何解析顶点数据（应用到逐个顶点属性上）
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(VAO);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		CustomRender();
		
		/* 更新着色器 */
		glUseProgram(shaderprogram);
		float time = glfwGetTime();
		float greenValue = sin(time) / 2.0f + 0.5f ;
		int vertcolor = glGetUniformLocation(shaderprogram,"ourColor");
		// 设置uniform值
		glUniform4f(vertcolor , 0.0f , greenValue , 0.0f , 1.0f );
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;

}
