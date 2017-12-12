#include "Test01.h"

// ������ɫ�� 
		const char *vertexShaderSource =
		"#version 330 core                   \n"
		"layout (location = 0) in vec3 aPos; \n" //λ�ñ�������ֵΪ 0 
		"out vec4 vertexColor ;              \n" //��ɫ��� 
		"void main()                         \n"
		"{                                   \n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"   vertexColor = vec4(0.5,0.0,0.0,1.0);\n"
		"}                                   \0"  ;

// ƬԴ��ɫ�� 
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

	// ����һ����ɫ������ ������ ������ɫ��

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// �������ɫ��Դ�븽�ӵ���ɫ��������
		/*
			glShaderSource������Ҫ�������ɫ��������Ϊ��һ��������
			�ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ����
			�����������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��
		*/
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//================= check compile errors ==========

	CheckCompileErrors(vertexShader);

	// ================ ƬԪ��ɫ�� ============ 

		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

	//================= check compile errors ==========
		
	CheckCompileErrors(fragmentShader);
		
	//====================  ���� shader ==================

	int shaderProgram = LinkShader(vertexShader, fragmentShader);

	// ================ set data============== 

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

	// =============== �����ݷ��͵� GPU �� 
		
		unsigned int VBO, VAO;
		// ����һ�� ����������� VAO 
		glGenVertexArrays(1, &VAO);
		// ����һ�� ���㻺����� VBO ��
		glGenBuffers(1, &VBO);
		// �� VAO 
		glBindVertexArray(VAO);
		// ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����  ��OpenGLʹ�� 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// ����glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ��� 
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ===============  ���Ӷ�������
		
		// ����OpenGL����ν�����������  ���ö�������ָ�� 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		// ����� 
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);

		// ��Ⱦѭ�� 
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
	// ����Ƿ����ɹ� ��
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	//���ʧ�� ����ӡ������Ϣ 
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
	// ����Ƿ����ɹ� ��
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

	//====================  ������Ӵ��� ==================

	CheckProgramErrors(shaderProgram);

	// �ڰ���ɫ���������ӵ���������Ժ󣬼ǵ�ɾ����ɫ���������ǲ�����Ҫ������ 
	glDeleteShader(vertext);
	glDeleteShader(frag);

	return shaderProgram;

}
