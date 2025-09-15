#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
const double RADIANS_TO_DEGREES = 180.0 / glm::pi<float>();

int main()
{
	glm::vec3 v(2, -1, 1);  //백터 생성
	glm::vec3 u(1, 1, 2);
	float d = glm::dot(v, u);  //d에 v와 u의 내적을 저장
	float c = d / (glm::length(u) * glm::length(v));  //c변수에 cos@ / |a||b|를 하여 cos@를 구함
	float deg = glm::acos(c) * RADIANS_TO_DEGREES;  // 
	std::cout << deg << std::endl;
	return 0;

}