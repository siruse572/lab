#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
const double RADIANS_TO_DEGREES = 180.0 / glm::pi<float>();

int main()
{
	/* <cos@ 구하기>
	glm::vec3 v(2, -1, 1);  //백터 생성
	glm::vec3 u(1, 1, 2);
	float d = glm::dot(v, u);  //d에 v와 u의 내적을 저장
	float c = d / (glm::length(u) * glm::length(v));  //c변수에 cos@ / |a||b|를 하여 cos@를 구함
	float deg = glm::acos(c) * RADIANS_TO_DEGREES;  // 
	std::cout << deg << std::endl;
	*/
	//glm::radians(60);  알아보기
	//degrees();

	/*
	glm::vec3 u (2, 0, 0);
	glm::vec3 v(-1, 1, 0);
	v = glm::normalize(v);
	u = glm::normalize(u);
	float d = glm::dot(u, v);
	std::cout << d << std::endl;
	*/
	
	/* < 백터 쪼개기>
	glm::vec3 v(1, 2, -1);
	glm::vec3 u(0, 1, 0);
	glm::vec3 b = glm::dot(v, u) * u;
	glm::vec3 a = v - b;
	std::cout << "a: " << glm::to_string(a) << std::endl;
	std::cout << "b: " << glm::to_string(b) << std::endl;
	return 0;
	*/

	glm::vec3 n(0, 1, 0);   //평면에서의 수직
	glm::vec3 p(1, 0, 1);  //평면 위에서의 점
	glm::vec3 x(-3, 3, 2);  //평면 밖의 점
	glm::vec3 v = x – p;
	n = glm::normalize(n);
	float d = glm::dot(v, u);
	return 0;
}