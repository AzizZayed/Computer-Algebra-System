cmake_minimum_required(VERSION 3.23)
project(cas)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

add_library(${PROJECT_NAME} scratch/scratch.cpp include/core/node/ExpressionProperties.h)
target_link_libraries(${PROJECT_NAME} src)