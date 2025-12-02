#define GLM_ENABLE_EXPERIMENTAL
#define GLM_SWIZZLE
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
const double RADIANS_TO_DEGREES = 180.0 / glm::pi<float>();

int main()
{

	//(1)  cross로 외적을 구하고 그 값으로 길이 즉 스칼라 값으로 변환한 것과 내적을 이용하여 각을 구하고, 그걸 바탕으로 sin@를 이용한 값과 비교
	glm::vec3 u(1, 0, 0);
	glm::vec3 v(-1, 1, 0);
	glm::vec3 c = glm::cross(u, v); // 외적 구하기 axb
	
	float l = glm::length(c);  //스칼라 값으로 변환 |axb|
	float ang = glm::acos(glm::dot(u, v) / (glm::length(u) * glm::length(v)));  //각도 구하기

	float l2 = glm::length(u) * glm::length(v) * sin(ang); // l == l2; 각도를 구한것으로 |a||b|*sin@로 |axb| 구하기
	//(2)

	glm::vec3 u2(1, 0, 0);
	glm::vec3 v2(0, 1, 0);
	float area = glm::length(glm::cross(u2, v2));  //외적의 넓이는 두 백터의 평행사변형의 넓이와 같음

	//(3)  평행하면 평행사변형의 면적이 없기에 0이 출력됨

	glm::vec3 u3(1, 0, 0);
	glm::vec3 v3(1, 0, 0); // 평행하기에 넓이가 0이 나옴

	//(4) 포인트로 백터를 구하여 그것을 외적을 구한 후 그 평행사변형을 반으로 쪼개어, 삼각형 넓이 구하기

	glm::vec3 p1(1, 0, 0); //these are all points, not vector 
	glm::vec3 p2(1, 1, 0);
	glm::vec3 p3(-1, 0, 0);
	glm::vec3 v1 = p2 - p1; glm::vec3 v2 = p3 - p1;
	float area = 0.5f * glm::length(glm::cross(v1, v2));  //삼각형의 넓이;

	//(5) 삼각형 normal 백터

	glm::vec3 p1(3.0f, 0.0f, 0.0f);
	glm::vec3 p2(1.5f, 0.86f, 0.0f);
	glm::vec3 p3(3.0f, 0.0f, -1.0f);

	glm::vec3 v1 = p2 - p1;
	glm::vec3 v2 = p3 - p1;
	glm::vec3 N = glm::normalize(glm::cross(v1, v2));//axb의 normalize
	std::cout << glm::to_string(N) << std::endl;

	return 0;
}