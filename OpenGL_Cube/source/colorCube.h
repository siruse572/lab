#ifndef COLORCUBE_H
#define COLORCUBE_H

#include <GL/gl3w.h>
#include <memory>

// ColorCube 클래스
// ▶ 큐브의 VAO/VBO/IBO를 관리하고, draw() 함수로 큐브를 그리는 역할
// ▶ PDF 42쪽까지 기준으로 작성
class ColorCube
{
private:
    // VAO 핸들 (Vertex Array Object)
    GLuint vaoHandle = 0;

    // VBO 핸들 (Vertex Buffer Object)
    GLuint vbo_cube_vertices = 0;  // 큐브 정점 좌표
    GLuint vbo_cube_colors = 0;    // 큐브 색상

    // IBO 핸들 (Index Buffer Object)
    GLuint ibo_cube_elements = 0;  // 큐브 인덱스

    // 내부 초기화 함수 (VAO/VBO/IBO 생성 및 데이터 업로드)
    void setup();

public:
    // 생성자에서 setup() 호출 → 큐브 데이터 초기화
    ColorCube();

    // 소멸자에서 glDelete* 호출 → GPU 리소스 해제
    ~ColorCube();

    // 큐브 그리기 함수
    void draw();

    // getter: VAO 핸들 반환 (필요 시 MyGlWindow에서 접근 가능)
    GLuint getVaoHandle() const { return vaoHandle; }
};

#endif // COLORCUBE_H