#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_transform_2d.hpp> // 2D 변환 함수 포함
#include <glm/mat3x2.hpp>          // 개념적으로는 2x3 (pdf 참조)

int main()
{
	glm::vec3 camPos(5, 5, 5);  // 카메라 위치
	glm::vec3 Look(0, 0, 0);  //물체 위치
	glm::vec3 Up(0, 1, 0); // up 백터
	glm::mat4 result = lookAt(camPos, Look, Up);
	std::cout << glm::to_string(result) << std::endl;

	return 0;
}
glm::mat4 lookAt(glm::vec3 campos, glm::vec3 Look, glm::vec3 Up)
{
	glm::vec3 z = glm::normalize(campos - Look);          
	glm::vec3 x = glm::normalize(glm::cross(Up, z));         
	glm::vec3 y = glm::cross(z, x); 
	glm::mat4 view = glm::mat4(1.0f);
	view[0][0] = x.x; view[0][1] = x.y; view[0][2] = x.z;
	view[1][0] = y.x; view[1][1] = y.y; view[1][2] = y.z;
	view[2][0] = z.x; view[2][1] = z.y; view[2][2] = z.z;
	glm::mat4 trans = glm::mat4(1.0f);
	trans[3][0] = -campos.x; trans[3][1] = -campos.y; trans[3][2] = -campos.z;
	glm::mat4 result = view * trans;
	return result;
}