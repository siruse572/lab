//#define GLFW_INCLUDE_GLU

#include <iostream>

#include <GL/gl3w.h>   //헬퍼함수
#include <GLFW/glfw3.h>
#include <memory>
#include "MyGlWindow.h"

std::unique_ptr<MyGlWindow> win; //스마트 포인터  / shard_ptr

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        // Initialization failed
        std::cout << "Error" << std::endl;
        return 0;

    }
    //오픈지엘 버전 저장 : 안써도 별 상관없음 : 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //오픈지엘 예전 기능은 다 빼고, 신 기능만 쓸래요 (예전 기능 사용하려면 : COMPATIBLE_PROFILE)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 800;
    int height = 800;
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL FrameWork", NULL, NULL);
    if (!window) {
        glfwTerminate();  //창을 만들어줌
        return -1;
    }
    //window가 제대로 생성 ->


    //openGL 컨텍스트 생성 -> 컨텍스트: 구조체(struct) 생성
    glfwMakeContextCurrent(window);//opengl 구조체 생성

    //헬퍼 초기화: opengl의 함수를 이용하기 위해 helper(loader)를 초기화
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


    //모니터의 refresh rate sync -> 1을 넣어서 하드웨어와 싱크를 맞춰줌/ 0을 넣으면 안 맞춰줌
    glfwSwapInterval(1); //enable vsync


    //MyGlWindow 클래스 객체 생성
    //스마트 포인터(필수): 자동으로 메모리반환해줌
    win = std::make_unique<MyGlWindow>(width, height);
    
    /*printf("OpenGL %s, GLSL %s\n",
        glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));*/
    
    while (!glfwWindowShouldClose(window))  //닫음 버튼을 누를때까지 안꺼지고 유지
    {
        //뭔가를 그려줘야 함
        
        //매 프레임 draw()함수 호출
        win->draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);          //키보드 및 마우스입력 등 이벤트를 감지하여 콜백 함수 호출
        /* Poll for and process events */
        glfwPollEvents();

    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}


