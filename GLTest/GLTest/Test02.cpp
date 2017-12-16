#include "Test01.h"

// ������ɫ�� 
		const char *vertexShaderSource =
		"#version 330 core                   \n"
		"layout (location = 0) in vec3 aPos; \n" //λ�ñ�������ֵΪ 0 
		"layout (location = 1) in vec3 aColor; \n"
		"out vec3 ourColor ;              \n" //��ɫ��� 
		"void main()                         \n"
		"{                                   \n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"	ourColor = aColor;                \n"
		"}                                   \0"  ;

// ƬԴ��ɫ�� 
		const char *fragmentShaderSource = 
		"	#version 330 core   \n"
		"	out vec4 FragColor; \n"
		"	in vec3 ourColor ; \n"
		"	void main()         \n"
		"	{                   \n"
		"		FragColor =vec4( ourColor,1.0);    \n"
		"	}                   \n\0" ;
		

// ��ϰshader �� Gpu ������� ��
int Test02()
{
	ConfigGLFwWindow();
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
			// λ��              // ��ɫ
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
			0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
		};

		float vertices2[] = {
			0.5f, 0.5f, 0.0f,   // ���Ͻ�
			0.5f, -0.5f, 0.0f,  // ���½�
			-0.5f, -0.5f, 0.0f, // ���½�
			-0.5f, 0.5f, 0.0f   // ���Ͻ�
		};

		float vertices3[] = {
			-1.0f ,0.0f ,0.0f ,
			0.0f , 1.0f ,0.0f,
			1.0f ,0.0f,0.0f,
			0.0f,-1.0f,0.0f
		};

		unsigned int indices[] = { // ע��������0��ʼ! 
			0, 1, 2, // ��һ��������
			4, 2, 3  // �ڶ���������
		};

	// =============== �����ݷ��͵� GPU �� 
		
		unsigned int VBO, VAO, EBO;
		// ����һ�� ����������� VAO 
		glGenVertexArrays(1, &VAO);
		// ����һ�� ���㻺����� VBO ��
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// �� VAO 
		glBindVertexArray(VAO);
		// ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����  ��OpenGLʹ�� 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ===============  ���Ӷ�������
		
		// ����OpenGL ����ν�����������  ���ö�������ָ�� 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//��ɫ����
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// ע����������ģ����� glVertexAttribPointer �� VBO ע��Ϊ�������Եİ󶨶��㻺������������֮�����ǿ��԰�ȫ�ؽ���� 
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		// ��VAO������ʱ����Ҫ�����EBO����Ϊ��Ԫ�ػ������IS�洢��VAO��; ����EBO��Լ����

		// ���VAO�İ󶨣����������� VAO �ĵ��þͲ���������޸����VAO����������������ٷ�����
		// �޸����� VAO ��Ҫ���� glBindVertexArray����������һ�㲻���ڲ�ֱ����Ҫ������½����VAO��Ҳ����VBO����
		glBindVertexArray(0);

		//��Ⱦģʽ ���߿�/�桿
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
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

			// ��������
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
				����1��������ȡֵ
					1.GL_TRIANGLES��ÿ������֮����������Σ�֮�䲻����
					2.GL_TRIANGLE_FAN����V0V1V2,V0V2V3,V0V3V4����������ʽ����������
					3.GL_TRIANGLE_STRIP��˳����ÿ��������֮������������Ρ�����������Ա�֤����ͬ�ķ��������������ξ������ơ���V0V1V2,V1V2V3,V2V3V4��������ʽ����������
				����2�������黺���е���һλ��ʼ���ƣ�һ�㶼����Ϊ0
				����3�����������
			*/

			//glDrawArrays(GL_TRIANGLES, 0, 5);

			/*
				glDrawElements(int mode , int Count , GL_UNSIGNED_SHORT ,  (GLvoid*)paryiFaces );
				�ڶ������� Count : �����ζ��������
				������������ ��������(indices)��Ԫ�ص����� 
					       GL_UNSIGNED_BYTE, 
						   GL_UNSIGNED_SHORT, 
						   GL_UNSIGNED_INT
				���ĸ����� paryiFaces : ��������������
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
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n " << infoLog << std::endl;
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
