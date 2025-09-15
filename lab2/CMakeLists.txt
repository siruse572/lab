cmake_minimum_required(VERSION 3.8)

# 프로젝트 이름 설정
project(lab1)

# MSVC Hot Reload 설정 (Visual Studio에서 디버깅 시 유용)
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# 외부 라이브러리 찾기
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)

# 소스 파일 수집
file(GLOB_RECURSE SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h"
)

# 인클루드 디렉토리 설정
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source")

# 실행 파일 생성
add_executable(lab1 ${SOURCES})

# 라이브러리 연결
target_link_libraries(lab1 PRIVATE glm::glm glfw unofficial::gl3w::gl3w)