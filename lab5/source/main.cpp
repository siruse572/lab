#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_transform_2d.hpp> // 2D 변환 함수 포함
#include <glm/mat3x2.hpp>          // 개념적으로는 2x3 (pdf 참조)

int main()
{
	glm::vec3 v(5, 6, 1); 
	glm::mat3 t(1.0); //identity matrix 
	t = glm::translate(t,glm::vec2(2, 3));
	v = t * v;
	std::cout << to_string(t) << std::endl; 
	std::cout << to_string(v) << std::endl; 
	return 0;
}