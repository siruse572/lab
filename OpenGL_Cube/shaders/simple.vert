#version 450

// cpu로부터 받은 속성 0번 입력: 정점 좌표 (vec3)
layout(location = 0) in vec3 vertexPosition; // VBO에서 넘기는 (x,y,z)

// cpu로부터 받은 속성 1번 입력: 정점 색상 (vec3)
layout(location = 1) in vec3 vertexColor;    // VBO에서 넘기는 (r,g,b)

// --- PDF에서 추가하라고 한 부분 ---
// CPU에서 전달받을 변환 행렬 uniform 변수
uniform mat4 model;      // 모델 변환 행렬
uniform mat4 view;       // 뷰(카메라) 변환 행렬
uniform mat4 projection; // 투영 변환 행렬

// 프래그먼트 셰이더로 넘길 색상
out vec3 fColor;

void main()
{
    // 좌표계 변환: 모델 → 뷰 → 프로젝션
    // PDF에서 지시한 대로 gl_Position을 변환된 좌표로 설정
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);

    // 색상 전달
    fColor = vertexColor;
}