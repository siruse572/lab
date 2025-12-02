#pragma once

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include "Loader.h"
#include "ColorCube.h"
#include "Viewer.h"

// MyGlWindow 클래스
class MyGlWindow {
public:
    // 기본 생성자
    MyGlWindow();

    // 인자 있는 생성자
    MyGlWindow(int w, int h);

    // 소멸자
    ~MyGlWindow();

    // 매 프레임 호출되는 draw 함수
    void draw();

    // 윈도우 크기 변경 시 호출
    void setSize(int w, int h) { m_width = w; m_height = h; }

    // 종횡비 변경 시 Viewer에 전달
    void setAspect(float aspect) { m_viewer->setAspectRatio(aspect); }

    // Viewer 접근용 getter
    Viewer* getViewer() const { return m_viewer.get(); }

private:
    // VAO 핸들
    GLuint vaohandle = 0;

    // ShaderProgram (Loader.h 기반)
    std::unique_ptr<ShaderProgram> shaderProgram;

    // 윈도우 크기
    int m_width = 0;
    int m_height = 0;

    // Cube 객체
    std::unique_ptr<ColorCube> m_cube;

    // Viewer 객체
    std::unique_ptr<Viewer> m_viewer;

    // Model / View / Projection 행렬
    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_projection;

    // 내부 초기화 함수
    void initialize();

    // 버퍼 생성 및 설정
    void setupBuffer();
};