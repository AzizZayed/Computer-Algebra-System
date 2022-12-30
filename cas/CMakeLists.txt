cmake_minimum_required(VERSION 3.12)
project(cas)

set(BUILD_CAS_TESTS ON CACHE BOOL "Build tests") # Disable tests
set(BUILD_CAS_BENCHMARK ON CACHE BOOL "Build benchmarks") # Disable benchmarks

add_subdirectory(src)

if (BUILD_CAS_TESTS)
    message(STATUS "Building CAS tests")
    enable_testing()
    add_subdirectory(tests)
endif()

if (BUILD_CAS_BENCHMARK)
    message(STATUS "Building CAS benchmarks")
    enable_testing()
    add_subdirectory(benchmark)
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE src)
