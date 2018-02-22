#include "MyCourses.h"

/*
*  矩阵变换
*/

int Test10()
{
	/*
	*  位移矩阵的使用 
	*/
	glm::vec4 vec(0.0f, 1.0f, 0.0f, 0.0f);
	// vec = 1 0 0 1 
	glm::mat4 trans;


	// 设置 trans 移动为  1 1 0 
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

	/*
	*  继续添加 旋转矩阵和缩放矩阵 
	*/
	// 沿z轴旋转90度  （ radians将角度转化为弧度 ）
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	
	
	// 每个轴都缩放到0.5倍
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	
	
	vec = trans * vec;
	// 0.5  2  0  
	std::cout << vec.x << "\n" <<vec.y << "\n" << vec.z << " " << std::endl;


	while (1)
	{
		;
	}
	return 0;
}