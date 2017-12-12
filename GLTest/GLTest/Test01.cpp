#include "Test01.h"


int Test01()
{
	
	CreatGLFwWindow();

	GLFWwindow* window = InitGLFWwindow();

	if (window == NULL)
	{
		return -1;
	}

	// 渲染循环(Render Loop)
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// ----- 用户交互 
		processInput(window);

		// custom render
		// ------ 自定义渲染 
		CustomRender();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		// 交换颜色缓冲 
		glfwSwapBuffers(window);
		// 检查有没有触发事件
		glfwPollEvents();
	}
	// 渲染循环结束后我们需要正确释放/删除之前的分配的所有资源 
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	// glfwGetKey(window , keycode按键代码 )   是否正在被按下  
	// 这里我们检查用户是否按下了返回键(Esc) 
	// glfwSetwindowShouldClose 使用把 WindowShouldClose 属性设置为 true 的方法关闭 GLFW 
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
	// glClearColor函数是一个状态设置函数，而glClear函数则是一个状态使用的函数，它使用了当前的状态来获取应该清除为的颜色。 
	// 先设置清屏的颜色 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//清空屏幕的颜色缓冲 （拿刚刚glClearColor设置的颜色去清屏）
	glClear(GL_COLOR_BUFFER_BIT);
}


void CreatGLFwWindow() {
	// glfw: initialize and configure
	// ------------------------------
	// 调用 glfwInit() 来初始化GLFW 
	glfwInit();
	//----------------- glfwWindowHint ( 选项的名称 , 选项的值 ) 配置 GLFW------ ------------------
	// 将主版本号(Major) 和 次版本号(Minor)都设为 3  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 告诉GLFW我们使用的是核心模式(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 如果使用的是苹果系统 就执行这一行 
#endif

}

GLFWwindow * InitGLFWwindow()
{
	// glfw 创建一个窗口对象 
	// --------------------
	// glfwCreateWindow(窗口的宽度，窗口的高度 ，“窗口名称（标题）”，null，null )  
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		// 创建窗口失败
		cout << " Failed to create GLFW window" << endl;
		// 终止程序 
		glfwTerminate();
		return NULL;
	}

	// 通知GLFW将我们窗口的上下文设置为当前线程的主上下文 
	glfwMakeContextCurrent(window);
	// 当用户改变窗口的大小的时候，视口也应该被调整 所以要注册回调函数  
	// 每当窗口改变大小，GLFW会调用 framebuffer_size_callback 函数 并填充相应的参数供你处理。 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: GLAD是用来管理OpenGL的函数指针的 
	// ---------------------------------------
	// 给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数  glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		// 如果创建失败 
		cout << "Failed to initialize GLAD" << endl;
		return NULL;
	}
	return window;
}

