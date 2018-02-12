#include "MyCourses.h"
/**
* 练习： 绘制两个连续的三角形 
* 
*/
int Test04()
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	ConfigGLFwWindow();
	GLFWwindow * window = InitGLFWwindow(SCR_WIDTH,SCR_HEIGHT);
	if (window == nullptr)
	{
		return -1;
	}
	
	int vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexshader);
	CheckCompileErrors(vertexshader);

	int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentshader);
	CheckCompileErrors(fragmentshader);
	int shaderprogram = LinkShader(vertexshader, fragmentshader);

	//两个连续的三角形 5个顶点 * 3位 * 4 字节 = 45字节 
	float vertices[] = {
		-1.0f, 0.0f, 0.0f,   
		-0.5f, 0.5f, 0.0f,
		0.0f,0.0f,0.0f,
		0.5f, 0.5f, 0.0f, 
		1.0f, 0.0f, 0.0f   
	};

	//索引数组 
	unsigned int indices[] = {  
		2, 3, 4, // 第一个三角形
		0, 1, 2  // 第二个三角形
	};
	unsigned int VBO, VAO, EBO;
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);
	
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 如何解析顶点数据（应用到逐个顶点属性上）
	glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE , 3*sizeof(float) , (void *) 0 ) ; 
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		CustomRender();
		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		// 绘制顶点个数 ，偏移 
		glDrawElements( GL_TRIANGLES, 6 , GL_UNSIGNED_INT , 0 );
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}