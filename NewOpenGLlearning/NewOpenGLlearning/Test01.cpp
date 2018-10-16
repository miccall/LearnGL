#include "MyCourses.h"
/**
* 第一课 ，初始化一个GL window 
*/
int Test01()
{
	// 配置GL-Window 用 GLFW 库  
	ConfigGLFwWindow();

	// 初始化窗口 
	GLFWwindow* window = InitGLFWwindow(SCR_WIDTH, SCR_HEIGHT);

	if (window == nullptr)
	{
		// 初始化失败
		return -1;
	}

	// 渲染循环(Render Loop)
	// ---------------------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window) /* 如果窗口没有关闭 */ )
	{
		// ----- 用户交互 
		processInput(window);

		// ------ 自定义渲染 
		CustomRender();

		// （ glfw: 交换缓冲区和轮询IO事件（ 按键/释放键，鼠标移动等 )
		// -------------------------------------------------------------------------------
		// 交换颜色缓冲 
		glfwSwapBuffers(window);
		// 检查有没有触发事件
		glfwPollEvents();
	}
	// 渲染循环 结束后 我们需要 正确 释放/删除 之前的分配的所有资源 
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}