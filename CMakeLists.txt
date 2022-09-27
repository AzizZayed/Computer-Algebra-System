cmake_minimum_required(VERSION 3.0)
project(ComputerAlgebraSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(${PROJECT_NAME} src/main.cpp)
add_subdirectory("cas")
target_link_libraries(${PROJECT_NAME} "cas")