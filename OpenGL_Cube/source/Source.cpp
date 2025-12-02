#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "MyGlWindow.h"

// --- 전역 상태 변수 ---
bool lbutton_down = false;
bool rbutton_down = false;
bool mbutton_down = false;
double m_lastMouseX = 0.0;
double m_lastMouseY = 0.0;
double cx = 0.0, cy = 0.0;

std::unique_ptr<MyGlWindow> win;

// --- 콜백 함수들 ---
void window_size_callback(GLFWwindow* window, int width, int height) {
    win->setSize(width, height);
    win->setAspect(width / (float)height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    cx = xpos;
    cy = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        m_lastMouseX = xpos;
        m_lastMouseY = ypos;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        lbutton_down = (action == GLFW_PRESS);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        rbutton_down = (action == GLFW_PRESS);
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        mbutton_down = (action == GLFW_PRESS);
    }
}

// --- 마우스 드래그 처리 ---
void mouseDragging(double width, double height) {
    if (lbutton_down) {
        float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
        float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
        win->getViewer()->rotate(fractionChangeX, fractionChangeY);
    }
    else if (mbutton_down) {
        float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
        win->getViewer()->zoom(fractionChangeY);
    }
    else if (rbutton_down) {
        float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
        float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);
        win->getViewer()->translate(-fractionChangeX, -fractionChangeY, 1);
    }
    m_lastMouseX = cx;
    m_lastMouseY = cy;
}

// --- main 함수 ---
int main(void) {
    if (!glfwInit()) {
        std::cout << "Error: GLFW 초기화 실패" << std::endl;
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 800, height = 800;
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL FrameWork", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return -1;
    }

    if (!gl3wIsSupported(3, 2)) {
        fprintf(stderr, "OpenGL 3.2 not supported\n");
        return -1;
    }
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
        glGetString(GL_SHADING_LANGUAGE_VERSION));

    glfwSwapInterval(1);

    win = std::make_unique<MyGlWindow>(width, height);

    // --- 콜백 등록 ---
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetKeyCallback(window, key_callback);

    // --- 루프 ---
    while (!glfwWindowShouldClose(window)) {
        win->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // 마우스 드래그 처리
        mouseDragging(width, height);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}