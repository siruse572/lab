#define GLM_ENABLE_EXPERIMENTAL

#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>         // glm::value_ptr
#include <glm/gtx/string_cast.hpp>      // glm::to_string
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, lookAt, perspective

// 생성자: 윈도우 크기를 받아 초기화
// 매개변수 w: 윈도우 너비 (픽셀 단위)
// 매개변수 h: 윈도우 높이 (픽셀 단위)
MyGlWindow::MyGlWindow(int w, int h)
{
    m_width = w;
    m_height = h;

    // Viewer 초기화 (카메라 위치 설정)
    glm::vec3 eye(5.0f, 5.0f, 5.0f);      // 카메라 위치
    glm::vec3 center(0.0f, 0.0f, 0.0f);   // 바라보는 중심점
    glm::vec3 up(0.0f, 1.0f, 0.0f);       // 위쪽 방향 벡터
    float aspect = static_cast<float>(w) / static_cast<float>(h); // 종횡비

    m_viewer = std::make_unique<Viewer>(eye, center, up, 45.0f, aspect);

    // --- 큐브 객체 생성 ---
    // ColorCube 클래스가 VAO/VBO/EBO를 내부에서 초기화하므로 여기서 생성만 해주면 됨
    m_cube = std::make_unique<ColorCube>();

    // --- 셰이더 초기화 ---
    setupBuffer();
}

// 소멸자: unique_ptr이 자동으로 리소스 해제
MyGlWindow::~MyGlWindow()
{
    // ColorCube와 ShaderProgram은 unique_ptr이 알아서 해제
    // vaohandle은 더 이상 직접 관리하지 않으므로 삭제 코드 제거 가능
}

// 셰이더 및 uniform 변수 초기화
void MyGlWindow::setupBuffer()
{
    // 셰이더 객체 생성
    shaderProgram = std::make_unique<ShaderProgram>();

    // 셰이더 파일 로딩
    shaderProgram->initFromFiles(
        "C:/CG/lab/OpenGL_Cube/shaders/simple.vert", // 버텍스 셰이더 경로
        "C:/CG/lab/OpenGL_Cube/shaders/simple.frag"  // 프래그먼트 셰이더 경로
    );

    // uniform 변수 등록 (셰이더에서 사용할 행렬들)
    shaderProgram->addUniform("model");
    shaderProgram->addUniform("view");
    shaderProgram->addUniform("projection");
}


// 매 프레임마다 호출되는 draw 함수
void MyGlWindow::draw(void)
{
    // --- 깊이 테스트 활성화 ---
    // Z-buffer를 사용해서 큐브의 앞뒤 면이 제대로 보이도록 설정
    glEnable(GL_DEPTH_TEST);

    // --- 배경색 설정 및 버퍼 초기화 ---
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // 배경색: 어두운 회색
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 컬러 + 깊이 버퍼 초기화

    // --- 뷰포트 설정 ---
    glViewport(0, 0, m_width, m_height); // 전체 윈도우 크기 기준으로 설정

    // --- 모델 행렬 계산 ---
    m_model = glm::mat4(1.0f); // 단위 행렬로 초기화
    m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, 0.0f)); // 위치 이동 없음
    m_model = glm::rotate(m_model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Y축 회전

    // --- 뷰 행렬 계산 ---
    glm::vec3 eye = m_viewer->getViewPoint();   // 카메라 위치
    glm::vec3 center = m_viewer->getViewCenter(); // 바라보는 중심점
    glm::vec3 up = m_viewer->getUpVector();     // 위쪽 방향
    m_view = glm::lookAt(eye, center, up);      // 뷰 행렬 생성

    // --- 프로젝션 행렬 계산 ---
    m_projection = glm::perspective(
        glm::radians(45.0f),                    // 시야각
        static_cast<float>(m_width) / m_height, // 종횡비
        0.1f,                                    // near plane
        500.0f                                   // far plane
    );

    // --- 셰이더 활성화 ---
    shaderProgram->use();

    // --- 셰이더에 행렬 전달 ---
    glUniformMatrix4fv(shaderProgram->uniform("model"), 1, GL_FALSE, glm::value_ptr(m_model));
    glUniformMatrix4fv(shaderProgram->uniform("view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(shaderProgram->uniform("projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

    // --- 큐브 그리기 ---
    // 기존처럼 VAO를 직접 바인딩하지 않고, ColorCube 객체의 draw() 호출
    // 내부에서 VAO 바인딩 + glDrawElements 처리됨
    m_cube->draw();

    // --- 셰이더 비활성화 ---
    shaderProgram->disable();
}