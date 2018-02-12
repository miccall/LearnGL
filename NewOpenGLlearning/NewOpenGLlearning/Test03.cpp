#include "MyCourses.h"
/**
* 第三课 ： 绘制一个矩形 
* 
* 索引缓冲对象的学习
* 
*/

int Test03() {
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
	GLFWwindow* window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == nullptr)
	{
		// 初始化失败
		return -1;
	}

	// =========================  创建shader =添加内容=编译=查错================================================================= 

	int vertshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertshader);
	CheckCompileErrors(vertshader);

	int fragshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragshader);
	CheckCompileErrors(fragshader);

	// =========================== 链接 shader =========================================================================================

	int shaderprogram = LinkShader(vertshader, fragshader);

	// ========================== 设置顶点数据 ===============================================================================

	// 一个矩形 ，有两个三角形构成，我们要绘制 4字节 * 18个 = 72 字节 
	/*
	float vertices[] = {
		// 第一个三角形
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, 0.5f, 0.0f,  // 左上角
		// 第二个三角形
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};
	
	这样是浪费的
	
	*/

	// 一个矩形的四个顶点 ，4字节 * 12 = 48字节  
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};

	// 矩形的索引在vertices[]里的顺序 
	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer( 0 , 3 , GL_FLOAT , GL_FALSE ,  3 * sizeof(float) , (void*)0 );
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	

	//线框模式渲染
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//填充模式渲染
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// 渲染循环(Render Loop)
	// ---------------------------------------------------------------------------------------------------------
	while ( !glfwWindowShouldClose(window) /* 如果窗口没有关闭 */)
	{
		// ----- 用户交互 
		processInput(window);

		// ------ 自定义渲染 
		CustomRender();

		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// （ glfw: 交换缓冲区和轮询IO事件（按键/释放键，鼠标移动等 )
		// -------------------------------------------------------------------------------
		// 交换颜色缓冲 
		//glBindVertexArray(0);
		glfwSwapBuffers(window);
		// 检查有没有触发事件
		glfwPollEvents();
	}
	// 渲染循环 结束后 我们需要 正确 释放/删除 之前的分配的所有资源 
	// ------------------------------------------------------------------

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}