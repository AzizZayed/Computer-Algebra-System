cmake_minimum_required(VERSION 3.2)
project(cas)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmark)

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE src)
