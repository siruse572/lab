#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_transform_2d.hpp> // 2D 변환 함수 포함
#include <glm/mat3x2.hpp>          // 개념적으로는 2x3 (pdf 참조)

/*
width = 780
height = 750
fovY = 45
nearz = 0.1
farz = 500

*/

glm::mat4 perspective(float fovy, float aspect, float near, float far)
{
    glm::mat4 projection(0.0f);
    float a = 1.0f / (aspect * tan(glm::radians(fovy) / 2.0f));
    float b = 1.0f / tan(glm::radians(fovy) / 2.0f);
    float c = -((far + near) / (far - near));
    float d = -(2.0f * far * near / (far - near));

    projection[0][0] = a;
    projection[1][1] = b;
    projection[2][2] = c;
    projection[2][3] = -1.0f;
    projection[3][2] = d;

    return projection;
}



int main()
{
    float width = 780.0f;
    float height = 750.0f;
    float fovY = 45.0f;
    float nearz = 0.1f;
    float farz = 500.0f;
    float aspect = width / height;
    glm::mat4 perspectiveMat = perspective(fovY, aspect, nearz, farz);
    std::cout << glm::to_string(perspectiveMat) << std::endl;
    return 0;
}

