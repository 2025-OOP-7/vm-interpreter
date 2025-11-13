cmake_minimum_required(VERSION 3.10)
project(VM-INTERPRETER)

# C++17 표준 지정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include 디렉터리 추가
include_directories(include)

# 소스 파일 수집
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 옵션 B 사용 중이므로 Instructions.cpp만 링크
# 실제로는 src/ 디렉터리의 모든 .cpp 파일이 포함되지만,
# Instructions.h/.cpp 한 쌍에 모든 구체 명령어를 모으는 구조임을 주의

# 실행 파일 생성
add_executable(interpreter ${SOURCES})

