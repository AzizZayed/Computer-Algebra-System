cmake_minimum_required(VERSION 3.0)
project(cas)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

add_library(${PROJECT_NAME} scratch/scratch.cpp)
target_link_libraries(${PROJECT_NAME} src)