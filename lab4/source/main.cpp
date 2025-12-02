#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/mat4x4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x2.hpp>  //개념적으로는 2x3(pdf참조)

int main()
{
	/*
	glm::mat2 m2 = { 1,0,1,-1 };
	std::cout << to_string(m2) << std::endl;

	glm::mat3x2 m3 = { {1,0}, {1,-1}, {0,1} };
	std::cout << to_string(m3) << std::endl;

	glm::mat4 m(1.0f);
	std::cout << to_string(m) << std::endl;
	*/

	/*
	glm::mat3 a = { { 1,1,-1 }, { 0,2,0 }, { 2,3,1 } };
	glm::mat3 b = { { 1,0,0}, {0,-1,1}, {0,1,2} };
	glm::mat2 m3 = a * b;
	glm::mat2 m4 = b * a;
	std::cout << "a * b = " << to_string(m3) << std::endl;
	std::cout << "b * a = " << to_string(m4) << std::endl;
	*/

	/*
	glm::mat2 m2 = { 1, 0, 1, -1 };
	glm::mat2 im = glm::inverse(m2);
	std::cout << to_string(im) << std::endl;  //역 행렬과 자기자신을 곱하면 단위 행렬이 나옴.

	glm::mat2 ii = m2 * im;
	std::cout << to_string(ii) << std::endl;
	*/

	glm::vec3 a(1, 2, 3);
	glm::mat3 a1{ {1,0,0}, {2,-1,0}, {0,0,1} };  //행렬과 백터와의 곱
	glm::vec3 b1 = a1 * a;  //곱을 할때는 행렬이 앞에 와야함

	std::cout << to_string(b1) << std::endl;

	return 0;
}