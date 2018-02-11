#include "MyCourses.h"
/**
* 第二课 ，绘制一个三角形
* 
* 顶点着色器 片元着色器的创立和编译 
* 顶带缓冲对象， 顶点数组对象的认识
* 
*/


int Test02()
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
	GLFWwindow* window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);
	if (window == nullptr)
	{
		// 初始化失败
		return -1;
	}

	// =========================  创建shader =添加内容=编译=查错================================================================= 
	
	int vertshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertshader , 1 , &vertexShaderSource , NULL );
	glCompileShader(vertshader);
	CheckCompileErrors(vertshader);

	int fragshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragshader, 1, &fragmentShaderSource, NULL );
	glCompileShader(fragshader);
	CheckCompileErrors(fragshader);
	
	// =========================== 链接 shader =========================================================================================
	
	int shaderprogram = LinkShader(vertshader, fragshader);

	// ========================== 设置顶点数据 ===============================================================================
	
	// xyz，xyz，xyz 【 三角形的三个点 】 4个字节 * 9个 == 36字节 
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};
	
	// ======================   把数据发送到 GPU 上     ====vbo对象 绑定vbo 发送vbo ================================================================================
	unsigned int VBO;
	// 生成VBO 
	glGenBuffers(1, &VBO);
	// 绑定vbo
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	// 把 数据 复制 到当前绑定的 缓冲 
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices , GL_STATIC_DRAW ); 

	// ======================  VAO 对象 ==============================================
	unsigned int VAO ;
	//生成 VAO
	glGenVertexArrays( 1 , &VAO ); 
	//绑定VAO 
	glBindVertexArray(VAO);
	// 3. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0 );
	glEnableVertexAttribArray(0);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	
	// 解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// 渲染循环(Render Loop)
	// ---------------------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window) /* 如果窗口没有关闭 */)
	{
		// ----- 用户交互 
		processInput(window);

		// ------ 自定义渲染 
		CustomRender();

		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES , 0 ,3 );

		// （ glfw: 交换缓冲区和轮询IO事件（按键/释放键，鼠标移动等 )
		// -------------------------------------------------------------------------------
		// 交换颜色缓冲 
		glfwSwapBuffers(window);
		// 检查有没有触发事件
		glfwPollEvents();
	}
	// 渲染循环 结束后 我们需要 正确 释放/删除 之前的分配的所有资源 
	// ------------------------------------------------------------------

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;

}