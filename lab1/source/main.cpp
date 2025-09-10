#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

int main()
{
	glm::vec3 p(1, 4, -5);
	glm::vec3 v(5, 1, 4);
	std::cout << to_string(p + v) << std::endl;  
	//2
	glm::vec3 v1(1, 0, 0);
	glm::vec3 v2(0, 1, 0);
	std::cout << to_string(v1 + v2) << std::endl;  
	//3
	glm::vec3 v3(0, 1, 0); 
	std::cout << to_string(2.0f * v3) << std::endl;  
	//4
	glm::vec3 v4(8, 2, 5);
	glm::vec3 v5(1, -1, 4);
	std::cout << to_string(v5 - v4) << std::endl;  
	//5
	glm::vec3 v6(1, 3, 4);
	glm::vec3 v6_normalized = glm::normalize(v6);  
	std::cout << to_string(v6_normalized) << std::endl;
	//6
	glm::vec3 v7(1, -1, 4);
	glm::vec4 v8 = glm::vec4(v7, 0);
	std::cout << to_string(v8) << std::endl;

	return 0;

}