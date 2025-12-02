#define GLM_ENABLE_EXPERIMENTAL 
#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

MyGlWindow::MyGlWindow(int w, int h)

//==========================================================================
{
    m_width = w;
    m_height = h;

    setupBuffer();

}


void MyGlWindow::setupBuffer()
{

    //쉐이더 객체 생성 : modern c++
    shaderProgram = std::make_unique<ShaderProgram>();

    //load shaders : vertex shader랑 fragment shader 지정
    shaderProgram->initFromFiles(
        "C:/CG/lab/OpenGL_basic/shaders/simple.vert",
        "C:/CG/lab/OpenGL_basic/shaders/simple.frag"
    );
    /*
    const float vertexPosition[] = {
       -0.2f, 0.0f, 0.0f, 1.0f,
       0.0f, 0.4f, 0.0f, 1.0f,
       0.2f, 0.0f, 0.0f, 1.0f,
    };

    //삼각형 색상 저장 / 속성 번호 : 1번
    const float vertexColor[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
    };

    const float vertices[] = { //interleave 방식
    -0.2f, 0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, //position, color for v0
    0.0f, 0.4f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, //position, color for v1
    0.2f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, //position, color for v2
    };
    */

    //삼각형의 정보 배열에 저장

    //Non-DSA(Direct State Access) 방식
    // 자꾸 바인딩 해야함 -> 바인딩 없에고 나온 방식 = DSA방식
    // 
    //삼각형 위치 저장 / 4개인 이유? -> x, y, z, w (w는 동차좌표계에서 사용) / 속성 번호 : 0번
    //const float vertexPosition[] = {
    //   -0.2f, 0.0f, 0.0f, 1.0f,
    //   -0.2f, 0.4f, 0.0f, 1.0f,
    //    0.2f, 0.0f, 0.0f, 1.0f,

    //    //앞의 2개는 GL_TRIANGLE_STRIP에서 자동으로 생성
    //    0.2f, 0.4f, 0.0f, 1.0f

    //};

    ////삼각형 색상 저장 / 속성 번호 : 1번
    //const float vertexColor[] = {
    //    1.0f, 0.0f, 0.0f,
    //    0.0f, 1.0f, 0.0f,
    //    0.0f, 0.0f, 1.0f,

    //    1.0f, 0.0f, 0.0f
    //};


    ////이제 삼각형에 대한 정보를 CPU가 아닌 GPU에 보냄
    //// 삼각형이 가진 속성 정보 : 위치, 색상
    //// 
    ////1. VAO 생성(Vertex Array Object) : 컨테이너, 실제 속성 정보는 없음
    //glGenVertexArrays(1, &vaohandle); //VAO 컨테이너 생성, 앞의 숫자는 몇개 생성할지를 나타내는 것
    //glBindVertexArray(vaohandle); //바인드 ? 여러개의 vao중에(만일 여러개 있다면) 어떤거 사용할래?
    ////바인드 : activate의 의미, 난 앞으로 여기에 뭔가 작업을 할래라고 지정, 선언
    //// 
    ////2. VBO 생성(Vertex Buffer Object) : vertxe의 속성 정보 저장
    //// Position
    //GLuint vbo_position;
    //glGenBuffers(1, &vbo_position); // vertex 위치 정보를 저장하기 위한 vbo
    //glBindBuffer(GL_ARRAY_BUFFER, vbo_position); //vbo 바인딩 : activate

    ////데이터를 메인 메모리 -> GPU 메모리로 보낸 후 할당 : 마지막: usage
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), &vertexPosition, GL_STATIC_DRAW);

    ////GPU 한테 메모리에 올라온 데이터 해석 방법을 알려줌
    //glVertexAttribPointer( 
    //   0, // 속성 번호
    //   4, // 데이터 수(전체 X, vertex 당 데이터 수)
    //   GL_FLOAT, // 데이터 타입
    //   GL_FALSE, // normalize 여부
    //   0, //stride
    //   0 //offset
    //);
    ////속성 enable
    //glEnableVertexAttribArray(0); // 속성 번호 0번 enable
    ////---------------------[ 삼각형의 위치 정보 저장 완료 ]------------------------

    //// Color
    //GLuint vbo_Color;
    //glGenBuffers(1, &vbo_Color); // vertex 색상 정보를 저장하기 위한 vbo
    //glBindBuffer(GL_ARRAY_BUFFER, vbo_Color); //vbo 바인딩 : activate

    ////데이터를 메인 메모리 -> GPU 메모리로 보낸 후 할당 : 마지막: usage
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);

    ////GPU 한테 메모리에 올라온 데이터 해석 방법을 알려줌
    //glVertexAttribPointer(
    //   1, // 속성 번호
    //   3, // 데이터 수(전체 X, vertex 당 데이터 수)
    //   GL_FLOAT, // 데이터 타입
    //   GL_FALSE, // normalize 여부
    //   0, //stride
    //   0 //offset
    //);
    //glEnableVertexAttribArray(1); // 속성 번호 1번 enable

    ////vao unbound vao 사용 중단(0 넣으면 됨)
    //glBindVertexArray(0);




    //non dsa
    //const float vertices[] = { //interleave 방식
    //   -0.2f, 0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 0.0f, //position, color for v0
    //    0.0f, 0.4f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f, //position, color for v1
    //    0.2f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, //position, color for v2
    //};

    //glGenVertexArrays(1, &vaohandle); //컨테이너 생성
    //glBindVertexArray(vaohandle); //binding
    //   GLuint vbo_vertex;
    //   glGenBuffers(1, &vbo_vertex);
    //   glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex); //vbo binding -> activate 
    //   //copy data from CPU to GPU
    //   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    //   //GPU에서 해석방법 알려줘야 함
    //   //위치(position) 처리
    //   glVertexAttribPointer(
    //      0,   // 속성(attribute) 번호
    //      4, // vertex 당 데이터 수 (position : x,y,z,w)
    //      GL_FLOAT, // 데이터 타입
    //      GL_FALSE, // normalize 여부
    //      sizeof(float) * 7,   //위치가 시작 한 후에, 얼마 데이터 후에 다시 위치가 시작하나? : stride(보폭)
    //      (void*)0   // offset : 위치 데이터가 시작하는 위치 / 그냥 0을 사용하면 오류가 남 따라서 void* 형으로 바꿈
    //   );

    //   glEnableVertexAttribArray(0); //속성 enable

    //   //색상(color) 처리
    //   glVertexAttribPointer(
    //      1,   // 속성(attribute) 번호
    //      3, // vertex 당 데이터 수 (position : x,y,z,w)
    //      GL_FLOAT, // 데이터 타입
    //      GL_FALSE, // normalize 여부
    //      sizeof(float) * 7,   //위치가 시작 한 후에, 얼마 데이터 후에 다시 위치가 시작하나? : stride(보폭)
    //      (void*)(sizeof(float) * 4)   // offset : 위치 데이터가 시작하는 위치 / 그냥 숫자를 사용하면 오류가 남 따라서 void* 형으로 바꿈
    //   );

    //   glEnableVertexAttribArray(1); //속성 enable

    
    /*
    //DSA 방식 -> 함수 명이 다름 / 빠르고 간편함 (glBinding*** 이 없음)

    //1. vao 생성
    GLuint vbo_position;
    GLuint vbo_color;
    //glCreate**** -> DSA 방식
    glCreateVertexArrays(1, &vaohandle); //vao 생성
    glCreateBuffers(1, &vbo_position); //vbo 생성
    glCreateBuffers(1, &vbo_color); //vbo 생성

    //position 처리
    // 
    //GPU 메모리 할당
    glNamedBufferData(vbo_position, sizeof(vertexPosition), vertexPosition, GL_STATIC_DRAW);
    //GPU에게 해석 방법을 알려줌
    glVertexArrayVertexBuffer(
        vaohandle, //vao
        0,   //binding index 번호
        vbo_position, //vbo
        0, //offset
        sizeof(float) * 4 //stride
    );

    //color 처리
    // 
    //GPU 메모리 할당
    glNamedBufferData(vbo_color, sizeof(vertexColor), vertexColor, GL_STATIC_DRAW);
    //GPU에게 해석 방법을 알려줌
    glVertexArrayVertexBuffer(
        vaohandle, //vao
        1,   //binding index 번호
        vbo_color, //vbo
        0, //offset
        sizeof(float) * 3 //stride
    );

    //속성(attribute) 설정 : position
    glVertexArrayAttribFormat(
        vaohandle,
        0, //속성(attribute) 번호 / binding index 번호와 다를 수 있음
        4, //vertex 당 데이터 수
        GL_FLOAT, //데이터 타입
        GL_FALSE, //normalize 여부
        0 //offset
    );

    glVertexArrayAttribBinding( // 속성 번호와 binding index 번호 연결 시켜주는 함수
        vaohandle,
        0,   // 속성 번호
        0 // binding index 번호
    );

    glEnableVertexArrayAttrib(vaohandle, 0); //0번 속성 enable

    //속성(attribute) 설정 : color
    glVertexArrayAttribFormat(
        vaohandle,
        1, //속성(attribute) 번호 / binding index 번호와 다를 수 있음
        3, //vertex 당 데이터 수
        GL_FLOAT, //데이터 타입
        GL_FALSE, //normalize 여부
        0 //offset
    );

    glVertexArrayAttribBinding( // 속성 번호와 binding index 번호 연결 시켜주는 함수
        vaohandle,
        1,   // 속성 번호
        1 // binding index 번호
    );

    glEnableVertexArrayAttrib(vaohandle, 1); //1번 속성 enable
    */

    //DSA - Interleave 방식으로

    /*
    GLuint vbo_vertex;
    glCreateVertexArrays(1, &vaohandle);
    glCreateBuffers(1, &vbo_vertex);

    glNamedBufferData(vbo_vertex, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexArrayVertexBuffer(vaohandle, 0, vbo_vertex, 0, sizeof(float) * 7);

    glVertexArrayAttribFormat(vaohandle, 0, 4, GL_FLOAT, GL_FALSE, 0);  //마지막 0: offset
    glVertexArrayAttribBinding(vaohandle, 0, 0); //0: 속성번호 0: 바인딩 인덱스
    glEnableVertexArrayAttrib(vaohandle, 0);  //속성번호 0 enable

    glVertexArrayAttribFormat(vaohandle, 1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4);  //마지막 0: offset
    glVertexArrayAttribBinding(vaohandle, 1, 0); //1: 속성번호 0: 바인딩 인덱스
    glEnableVertexArrayAttrib(vaohandle, 1);  //속성번호 1 enable

    */


//cube 만들기(non dsa - index 이용)
GLfloat cube_vertices[] = {
    // front
    -1.0, -1.0, 1.0,
    1.0, -1.0, 1.0,
    1.0, 1.0, 1.0,
    -1.0, 1.0, 1.0,
    // back
    -1.0, -1.0, -1.0,
    1.0, -1.0, -1.0,
    1.0, 1.0, -1.0,
    -1.0, 1.0, -1.0,
};
GLfloat cube_colors[] = {
    // front colors
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0,
    // back colors 
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0,
};

GLushort cube_elements[] = {
   0, 1, 2,   2, 3, 0,   1, 5, 6,
   6, 2, 1,   7, 6, 5,   5, 4, 7,
   4, 0, 3,   3, 7, 4,   4, 5, 1,
   1, 0, 4,   3, 2, 6,   6, 7, 3,
};
/*
glGenVertexArrays(1, &vaohandle); //컨테이너 생성
glBindVertexArray(vaohandle); //Bind ? 여러개의 vao중에(만일 여러개 있다면) 어떤거 사용할래?
//Bind : activate의미, 난 앞으로 여기에 뭔가 작업을 할래라고 지정, 선언
// 
//2. VBO 생성(Vertex Buffer Object의 약자) : vertex의 속성 정보 저장
GLuint vbo_positon;
glGenBuffers(1, &vbo_positon); //vertex 위치 정보를 저장하기 위한 vbo
glBindBuffer(GL_ARRAY_BUFFER, vbo_positon); //vbo 바인딩 : activate
glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

//데이터를 메인 메모리 -> GPU메모리로 보낸 후 할당 : 마지막 : usage //변경할려면 다이나믹으로 변경
glVertexAttribPointer( //GPU 한테, 메모리에 올라온 데이터 해석 방법을 알려줌
    0, //속성 번호
    3, //데이터 수
    GL_FLOAT, //데이터 타입
    GL_FALSE, //normalize 여부
    0, //stride
    0 //offset
);
//속성 enable
glEnableVertexAttribArray(0); //속성 번호 0번 enable

GLuint vbo_color;
glGenBuffers(1, &vbo_color); //vertex 색상 정보를 저장하기 위한 vbo
glBindBuffer(GL_ARRAY_BUFFER, vbo_color); //vbo 바인딩 : activate

//데이터를 메인 메모리 -> GPU메모리로 보낸 후 할당 : 마지막 : usage //변경할려면 다이나믹으로 변경
glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
glVertexAttribPointer( //GPU 한테, 메모리에 올라온 데이터 해석 방법을 알려줌
    1, //속성 번호
    3, //데이터 수
    GL_FLOAT, //데이터 타입
    GL_FALSE, //normalize 여부
    0, //stride
    0 //offset
);
glEnableVertexAttribArray(1); //속성 번호 1번 enable

GLuint ibo_cube_elements;
glGenBuffers(1, &ibo_cube_elements);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);




//vao unbound
glBindVertexArray(0); //현재 사용중인 vao unbound(0을 넣으면 됨)
*/

GLuint vbo_position;
GLuint vbo_color;
//glCreate**** -> DSA 방식
glCreateVertexArrays(1, &vaohandle); //vao 생성
glCreateBuffers(1, &vbo_position); //vbo 생성
glCreateBuffers(1, &vbo_color); //vbo 생성

//position 처리
// 
//GPU 메모리 할당
glNamedBufferData(vbo_position, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
//GPU에게 해석 방법을 알려줌
glVertexArrayVertexBuffer(
    vaohandle, //vao
    0,   //binding index 번호
    vbo_position, //vbo
    0, //offset
    sizeof(float) * 3 //stride
);

//color 처리
// 
//GPU 메모리 할당
glNamedBufferData(vbo_color, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
//GPU에게 해석 방법을 알려줌
glVertexArrayVertexBuffer(
    vaohandle, //vao
    1,   //binding index 번호
    vbo_color, //vbo
    0, //offset
    sizeof(float) * 3 //stride
);

//속성(attribute) 설정 : position
glVertexArrayAttribFormat(
    vaohandle,
    0, //속성(attribute) 번호 / binding index 번호와 다를 수 있음
    3, //vertex 당 데이터 수
    GL_FLOAT, //데이터 타입
    GL_FALSE, //normalize 여부
    0 //offset
);

glVertexArrayAttribBinding( // 속성 번호와 binding index 번호 연결 시켜주는 함수
    vaohandle,
    0,   // 속성 번호
    0 // binding index 번호
);

glEnableVertexArrayAttrib(vaohandle, 0); //0번 속성 enable

//속성(attribute) 설정 : color
glVertexArrayAttribFormat(
    vaohandle,
    1, //속성(attribute) 번호 / binding index 번호와 다를 수 있음
    3, //vertex 당 데이터 수
    GL_FLOAT, //데이터 타입
    GL_FALSE, //normalize 여부
    0 //offset
);

glVertexArrayAttribBinding( // 속성 번호와 binding index 번호 연결 시켜주는 함수
    vaohandle,
    1,   // 속성 번호
    1 // binding index 번호
);
GLuint ibo_cube_elements;
glEnableVertexArrayAttrib(vaohandle, 1); //1번 속성 enable
glCreateBuffers(1, &ibo_cube_elements); //Gluint ibo_cube_elements
glNamedBufferData(ibo_cube_elements, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW); glVertexArrayElementBuffer(vaohandle, ibo_cube_elements);
}


void MyGlWindow::draw(void)
{

    
    
    glClearColor(0.2, 0.2, 0.2, 1); // 백그라운드 색상 지정 (R, G, B, A) / A는 알파
    //어떤 버퍼를 지울지 지정 : 라스터라이제이션 할때 두 개의 버퍼 : color, depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //0. 뷰포트 설정 : 캔버스 크기 및 위치 설정 : 현재는 800x800인데, 이걸 다 쓸건지
    //일부만 쓸건지 결정

    glViewport(0, 0, m_width, m_height); // 앞 두개 값 : 시작점, 뒤 두개 값 : 크기


    //1. 쉐이더 USE
    shaderProgram->use();

    //2. vao binding
    glBindVertexArray(vaohandle);

    //3. call draw function
    //index가 없을 때 그리기
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3); //어떻게 그릴래? (삼각형으로, 시작 인덱스, 버텍스 수)
    //primitive , 총 3가지 Point, line, triangle
//GL_TRIANGLES : 3개씩 끊어서 삼각형 그리기(직접 추가해서 그리기) 꼭짓점 6개 필요
//GL_TRIANGLE_STRIP : 3개 이후부터는 이전 2개와 이어서 삼각형 그리기 (자동으로 반복) 꼭짓점 4개 필요


    //cube draw 함수(인덱스가 있을 때)
    int size; 
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size); 
    glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);



//4. 쉐이더 disable
    shaderProgram->disable();
}
