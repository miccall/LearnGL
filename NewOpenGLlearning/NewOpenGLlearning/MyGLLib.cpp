#include "MyGLLib.h"

void miccall::ConfigGLFwWindow(){
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

GLFWwindow * miccall::InitGLFWwindow(unsigned int SCR_WIDTH , unsigned int SCR_HEIGHT )
{
	// glfw 创建一个窗口对象 
	// --------------------
	// glfwCreateWindow(窗口的宽度，窗口的高度 ，“窗口名称（标题）”，null，null )  
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == nullptr)
	{
		// 创建窗口失败
		cout << " Failed to create GLFW window" << endl;
		// 终止程序 
		glfwTerminate();
		return nullptr;
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


void miccall::CheckCompileErrors(int shader)
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

void miccall::CheckProgramErrors(int program)
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


int miccall::LinkShader(int &vertex, int &frag)
{
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, frag);
	glLinkProgram(shaderProgram);

	//====================  检查链接错误 ==================

	CheckProgramErrors(shaderProgram);

	// 在把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们了 
	glDeleteShader(vertex);
	glDeleteShader(frag);

	return shaderProgram;

}

void miccall::processInput(GLFWwindow *window)
{
	// glfwGetKey(window , keycode按键代码 )   是否正在被按下  
	// 这里我们检查用户是否按下了返回键(Esc) 
	// glfwSetwindowShouldClose 使用把 WindowShouldClose 属性设置为 true 的方法关闭 GLFW 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void miccall::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void miccall::CustomRender()
{
	// glClearColor函数是一个状态设置函数，而glClear函数则是一个状态使用的函数，它使用了当前的状态来获取应该清除为的颜色。 
	// 先设置清屏的颜色 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//清空屏幕的颜色缓冲 （拿刚刚glClearColor设置的颜色去清屏）
	glClear(GL_COLOR_BUFFER_BIT);
}