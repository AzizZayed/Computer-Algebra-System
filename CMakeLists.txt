cmake_minimum_required(VERSION 3.0)
project(ComputerAlgebraSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(
            -O0
            -Wall
            -Wextra
#            -ffast-math # Is this supported for all compilers?
            -fsanitize=address
            -fsanitize=undefined
            -fno-sanitize-recover=all
            -fno-omit-frame-pointer
    )
    link_libraries(
            -fsanitize=address
            -fsanitize=undefined
    )
endif()

add_executable(${PROJECT_NAME} src/main.cpp)
add_subdirectory("cas")
target_link_libraries(${PROJECT_NAME} "cas")