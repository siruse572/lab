#include "ColorCube.h"

// --- 큐브 데이터 (cpp 내부에만 정의) ---
// 정점 좌표 (8개 꼭짓점, 각 꼭짓점은 x,y,z 3개의 값)
static const GLfloat cube_vertices[] = {
    // front face (앞면)
    -1.0f, -1.0f,  1.0f,  // 0번 정점
     1.0f, -1.0f,  1.0f,  // 1번 정점
     1.0f,  1.0f,  1.0f,  // 2번 정점
    -1.0f,  1.0f,  1.0f,  // 3번 정점
    // back face (뒷면)
    -1.0f, -1.0f, -1.0f,  // 4번 정점
     1.0f, -1.0f, -1.0f,  // 5번 정점
     1.0f,  1.0f, -1.0f,  // 6번 정점
    -1.0f,  1.0f, -1.0f   // 7번 정점
};

// 정점 색상 (각 꼭짓점에 RGB 색상 지정)
static const GLfloat cube_colors[] = {
    // front colors
    1.0f, 0.0f, 0.0f,  // 빨강 (0번 정점)
    0.0f, 1.0f, 0.0f,  // 초록 (1번 정점)
    0.0f, 0.0f, 1.0f,  // 파랑 (2번 정점)
    1.0f, 1.0f, 1.0f,  // 흰색 (3번 정점)
    // back colors
    1.0f, 0.0f, 0.0f,  // 빨강 (4번 정점)
    0.0f, 1.0f, 0.0f,  // 초록 (5번 정점)
    0.0f, 0.0f, 1.0f,  // 파랑 (6번 정점)
    1.0f, 1.0f, 1.0f   // 흰색 (7번 정점)
};

// 인덱스 (삼각형 12개 → 총 36개 인덱스)
// 각 면을 두 개의 삼각형으로 구성
static const GLushort cube_elements[] = {
    0, 1, 2,   2, 3, 0,  // front
    1, 5, 6,   6, 2, 1,  // right
    7, 6, 5,   5, 4, 7,  // back
    4, 0, 3,   3, 7, 4,  // left
    4, 5, 1,   1, 0, 4,  // bottom
    3, 2, 6,   6, 7, 3   // top
};

// 생성자: 객체가 만들어질 때 setup() 호출 → VAO/VBO/EBO 초기화
ColorCube::ColorCube() {
    setup();
}

// 소멸자: GPU 리소스 해제
ColorCube::~ColorCube() {
    glDeleteVertexArrays(1, &vaoHandle);
    glDeleteBuffers(1, &vbo_cube_vertices);
    glDeleteBuffers(1, &vbo_cube_colors);
    glDeleteBuffers(1, &ibo_cube_elements);
}

// 초기화 함수: VAO/VBO/EBO 생성 및 데이터 업로드
void ColorCube::setup() {
    // --- VAO 생성 ---
    // VAO: 정점 배열 객체 → 정점 속성 설정을 저장하는 컨테이너
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);

    // --- VBO: 정점 좌표 ---
    // glGenBuffers(1, &vbo_cube_vertices): 버퍼 객체 생성
    // glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices): 현재 바인딩된 VBO로 지정
    // glBufferData: 실제 데이터를 GPU 메모리에 업로드
    glGenBuffers(1, &vbo_cube_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer:
    // (location=0, size=3, type=GL_FLOAT, normalized=GL_FALSE, stride=0, pointer=0)
    // → 셰이더의 layout(location=0) vec3 vertexPosition에 연결
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // --- VBO: 정점 색상 ---
    glGenBuffers(1, &vbo_cube_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);

    // layout(location=1) vec3 vertexColor에 연결
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // --- EBO: 인덱스 버퍼 ---
    // GL_ELEMENT_ARRAY_BUFFER에 인덱스 데이터 업로드
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

    // VAO 언바인딩 (정리)
    glBindVertexArray(0);
}

// 큐브 그리기 함수
void ColorCube::draw() {
    // VAO 바인딩 → 정점 속성/버퍼 설정 복원
    glBindVertexArray(vaoHandle);

    // IBO 크기 확인 후 그리기
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    // glDrawElements:
    // mode=GL_TRIANGLES → 삼각형으로 그림
    // count=size/sizeof(GLushort) → 인덱스 개수
    // type=GL_UNSIGNED_SHORT → 인덱스 자료형
    // indices=0 → 현재 바인딩된 EBO에서 읽음
    glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

    // VAO 언바인딩
    glBindVertexArray(0);
}