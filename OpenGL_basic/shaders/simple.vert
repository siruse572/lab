#version 450 

//cpu로 부터 받은 속성 0번의 입력을 vec4로 받음
layout(location = 0) in vec4 vertexPosition; //4개의 값이므로 vec4
//cpu로 부터 받은 속성 1번의 입려을 vec3로 받음
layout(location = 1) in vec3 vertexColor;  //3개의 값이므로 vec3

out vec3 fColor;  //프레그먼트로 보낼 색상
void main()
{
//gl_Position은 빌트인 키워드로서, 클립좌표계를 받아들임
//나중에 자동으로 gl_Position 값을 perspective division을 해줌
//그런데 왜 좌표계 변환을 안하지? 이유는 지금 받은 vertexPosition이 클립 좌표계라고 했기 때문
//중요!: vertex shader에는 반드시 gl_Position값을 설정해야 함.
	gl_Position = vertexPosition; //그렇기에 바로 넣을 수 있음(필수)
	fColor = vertexColor;
}
