#include "Test01.h"


int Test01()
{
	
	CreatGLFwWindow();

	GLFWwindow* window = InitGLFWwindow();

	if (window == NULL)
	{
		return -1;
	}

	// ��Ⱦѭ��(Render Loop)
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// ----- �û����� 
		processInput(window);

		// custom render
		// ------ �Զ�����Ⱦ 
		CustomRender();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		// ������ɫ���� 
		glfwSwapBuffers(window);
		// �����û�д����¼�
		glfwPollEvents();
	}
	// ��Ⱦѭ��������������Ҫ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ 
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	// glfwGetKey(window , keycode�������� )   �Ƿ����ڱ�����  
	// �������Ǽ���û��Ƿ����˷��ؼ�(Esc) 
	// glfwSetwindowShouldClose ʹ�ð� WindowShouldClose ��������Ϊ true �ķ����ر� GLFW 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void CustomRender()
{
	// glClearColor������һ��״̬���ú�������glClear��������һ��״̬ʹ�õĺ�������ʹ���˵�ǰ��״̬����ȡӦ�����Ϊ����ɫ�� 
	// ��������������ɫ 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//�����Ļ����ɫ���� ���øո�glClearColor���õ���ɫȥ������
	glClear(GL_COLOR_BUFFER_BIT);
}


void CreatGLFwWindow() {
	// glfw: initialize and configure
	// ------------------------------
	// ���� glfwInit() ����ʼ��GLFW 
	glfwInit();
	//----------------- glfwWindowHint ( ѡ������� , ѡ���ֵ ) ���� GLFW------ ------------------
	// �����汾��(Major) �� �ΰ汾��(Minor)����Ϊ 3  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // ���ʹ�õ���ƻ��ϵͳ ��ִ����һ�� 
#endif

}

GLFWwindow * InitGLFWwindow()
{
	// glfw ����һ�����ڶ��� 
	// --------------------
	// glfwCreateWindow(���ڵĿ�ȣ����ڵĸ߶� �����������ƣ����⣩����null��null )  
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		// ��������ʧ��
		cout << " Failed to create GLFW window" << endl;
		// ��ֹ���� 
		glfwTerminate();
		return NULL;
	}

	// ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳��������� 
	glfwMakeContextCurrent(window);
	// ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ����� ����Ҫע��ص�����  
	// ÿ�����ڸı��С��GLFW����� framebuffer_size_callback ���� �������Ӧ�Ĳ������㴦�� 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: GLAD����������OpenGL�ĺ���ָ��� 
	// ---------------------------------------
	// ��GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���  glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ����� 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// �������ʧ�� 
		cout << "Failed to initialize GLAD" << endl;
		return NULL;
	}
	return window;
}

