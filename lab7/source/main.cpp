#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_transform_2d.hpp> // 2D 변환 함수 포함
#include <glm/mat3x2.hpp>          // 개념적으로는 2x3 (pdf 참조)

int main()
{
    glm::vec4 point(4.0f, 5.0f, 3.0f, 1.0f);
    glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(1.3f, 1.3f, 1.3f));
    glm::mat4 t = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 5.0f, 0.0f));

    glm::mat4 rx = glm::rotate(glm::mat4(1.0f), glm::radians(40.0f), glm::vec3(1.0f, 0, 0));
    glm::mat4 ry = glm::rotate(glm::mat4(1.0f), glm::radians(56.0f), glm::vec3(0, 1.0f, 0));

    glm::mat4 model = t * s * rx * ry;

    glm::vec4 worldPoint = model * point;

    //std::cout << glm::to_string(worldPoint) << std::endl;

    glm::mat4 view = { {0.83f, -0.3f, 0.47f, 0}, {0, 0.84f, 0.54f, 0}, {-0.56f, -0.45, 0.7f, 0}, {0, 0, -44.47f, 1} };
    //inverse(view)는 camera->world 행렬이 됨
    glm::mat4 inView = glm::inverse(view);
    //inview의 마지막 컬럼이카메라 위치가 됨
    glm::vec3 camPos = inView[3];  //카메라 위치
    //view 구성시, 3개의 축을 구했는데, 카메라는 -z방향을 바라본다고 가정
    //카메라는 -z축을 바라보고 있음
    glm::vec3 z_axis = glm::normalize(-inView[2]);
    glm::vec3 camTarget = camPos + z_axis * 10.0f;
    glm::vec3 up(0, 1, 0);
    glm::mat4 myView = lookAt(camPos, camTarget, up);
    std::cout << glm::to_string(myView) << std::endl;
    return 0;
}
