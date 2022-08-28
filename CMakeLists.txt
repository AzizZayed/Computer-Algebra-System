cmake_minimum_required(VERSION 3.23)
project(ComputerAlgebraSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory("cas")
target_link_libraries(${PROJECT_NAME} "cas")