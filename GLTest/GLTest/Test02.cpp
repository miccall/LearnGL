#include "Test01.h"

// 顶点着色器 
		const char *vertexShaderSource =
		"#version 330 core                   \n"
		"layout (location = 0) in vec3 aPos; \n" //位置变量属性值为 0 
		"out vec4 vertexColor ;              \n" //颜色输出 
		"void main()                         \n"
		"{                                   \n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"   vertexColor = vec4(0.5,0.0,0.0,1.0);\n"
		"}                                   \0"  ;

// 片源着色器 
		const char *fragmentShaderSource = 
		"	#version 330 core   \n"
		"	out vec4 FragColor; \n"
		"	in  vec4 vertexColor ; \n"
		"	void main()         \n"
		"	{                   \n"
		"		FragColor = vertexColor;    \n"
		"	}                   \n\0" ;
		

int Test02()
{
	CreatGLFwWindow();
	GLFWwindow * window = InitGLFWwindow();

	//=============== shader build ======== 

	// 创建一个着色器对象 类型是 顶点着色器

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 把这个着色器源码附加到着色器对象上
		/*
			glShaderSource函数把要编译的着色器对象作为第一个参数。
			第二参数指定了传递的源码字符串数量，这里只有一个。
			第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。
		*/
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//================= check compile errors ==========

	CheckCompileErrors(vertexShader);

	// ================ 片元着色器 ============ 

		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

	//================= check compile errors ==========
		
	CheckCompileErrors(fragmentShader);
		
	//====================  链接 shader ==================

	int shaderProgram = LinkShader(vertexShader, fragmentShader);

	// ================ set data============== 

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

	// =============== 把数据发送到 GPU 上 
		
		unsigned int VBO, VAO;
		// 生成一个 顶点数组对象 VAO 
		glGenVertexArrays(1, &VAO);
		// 生成一个 顶点缓冲对象 VBO ；
		glGenBuffers(1, &VBO);
		// 绑定 VAO 
		glBindVertexArray(VAO);
		// 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上  供OpenGL使用 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// 调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中 
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ===============  链接顶点属性
		
		// 告诉OpenGL该如何解析顶点数据  设置顶点属性指针 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		// 解除绑定 
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		// 渲染循环 
		while (!glfwWindowShouldClose(window))
		{
			// input
			// -----
			processInput(window);

			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw our first triangle
			glUseProgram(shaderProgram);
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glDrawArrays(GL_TRIANGLES, 0, 3);
			// glBindVertexArray(0); // no need to unbind it every time 

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();

	return 0 ;
}

void CheckCompileErrors(int shader)
{
	int  success;
	char infoLog[512];
	// 检查是否编译成功 。
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	//如果失败 ，打印错误信息 
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
}

void CheckProgramErrors(int program)
{
	int  success;
	char infoLog[512];
	// 检查是否编译成功 。
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}


int LinkShader(int &vertext, int &frag)
{
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertext);
	glAttachShader(shaderProgram, frag);
	glLinkProgram(shaderProgram);

	//====================  检查链接错误 ==================

	CheckProgramErrors(shaderProgram);

	// 在把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们了 
	glDeleteShader(vertext);
	glDeleteShader(frag);

	return shaderProgram;

}
