#include "Test01.h"

// 顶点着色器 
		const char *vertexShaderSource =
		"#version 330 core                   \n"
		"layout (location = 0) in vec3 aPos; \n" //位置变量属性值为 0 
		"layout (location = 1) in vec3 aColor; \n"
		"out vec3 ourColor ;              \n" //颜色输出 
		"void main()                         \n"
		"{                                   \n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	ourColor = aColor;                \n"
		"}                                   \0"  ;

// 片源着色器 
		const char *fragmentShaderSource = 
		"	#version 330 core   \n"
		"	out vec4 FragColor; \n"
		"	in vec3 ourColor ; \n"
		"	void main()         \n"
		"	{                   \n"
		"		FragColor =vec4( ourColor,1.0);    \n"
		"	}                   \n\0" ;
		

// 练习shader 和 Gpu 缓存对象 。
int Test02()
{
	ConfigGLFwWindow();
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
			// 位置              // 颜色
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
			0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
		};

		float vertices2[] = {
			0.5f, 0.5f, 0.0f,   // 右上角
			0.5f, -0.5f, 0.0f,  // 右下角
			-0.5f, -0.5f, 0.0f, // 左下角
			-0.5f, 0.5f, 0.0f   // 左上角
		};

		float vertices3[] = {
			-1.0f ,0.0f ,0.0f ,
			0.0f , 1.0f ,0.0f,
			1.0f ,0.0f,0.0f,
			0.0f,-1.0f,0.0f
		};

		unsigned int indices[] = { // 注意索引从0开始! 
			0, 1, 2, // 第一个三角形
			4, 2, 3  // 第二个三角形
		};

	// =============== 把数据发送到 GPU 上 
		
		unsigned int VBO, VAO, EBO;
		// 生成一个 顶点数组对象 VAO 
		glGenVertexArrays(1, &VAO);
		// 生成一个 顶点缓冲对象 VBO ；
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// 绑定 VAO 
		glBindVertexArray(VAO);
		// 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上  供OpenGL使用 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ===============  链接顶点属性
		
		// 告诉OpenGL 该如何解析顶点数据  设置顶点属性指针 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//颜色属性
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 注意这是允许的，调用 glVertexAttribPointer 将 VBO 注册为顶点属性的绑定顶点缓冲区对象，所以之后我们可以安全地解除绑定 
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		// 当VAO被激活时，不要解除绑定EBO，因为绑定元素缓冲对象IS存储在VAO中; 保持EBO的约束。

		// 解除VAO的绑定，这样其他的 VAO 的调用就不会意外地修改这个VAO，但是这种情况很少发生。
		// 修改其他 VAO 需要调用 glBindVertexArray，所以我们一般不会在不直接需要的情况下解除绑定VAO（也不是VBO）。
		glBindVertexArray(0);

		//渲染模式 【线框/面】
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
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

			// 画三角形
			glUseProgram(shaderProgram);
			/*
			float timeValue = glfwGetTime();
			float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
			glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
			*/

			glBindVertexArray(VAO); 
			// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			
			/*
				glDrawArrays(int mode, int first,int count)
				参数1：有三种取值
					1.GL_TRIANGLES：每三个顶之间绘制三角形，之间不连接
					2.GL_TRIANGLE_FAN：以V0V1V2,V0V2V3,V0V3V4，……的形式绘制三角形
					3.GL_TRIANGLE_STRIP：顺序在每三个顶点之间均绘制三角形。这个方法可以保证从相同的方向上所有三角形均被绘制。以V0V1V2,V1V2V3,V2V3V4……的形式绘制三角形
				参数2：从数组缓存中的哪一位开始绘制，一般都定义为0
				参数3：顶点的数量
			*/

			//glDrawArrays(GL_TRIANGLES, 0, 5);

			/*
				glDrawElements(int mode , int Count , GL_UNSIGNED_SHORT ,  (GLvoid*)paryiFaces );
				第二个参数 Count : 三角形顶点的数量
				第三个参数是 索引数组(indices)中元素的类型 
					       GL_UNSIGNED_BYTE, 
						   GL_UNSIGNED_SHORT, 
						   GL_UNSIGNED_INT
				第四个参数 paryiFaces : 三角形索引数组
			*/
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			
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
		glDeleteBuffers(1, &EBO);
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
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n " << infoLog << std::endl;
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
