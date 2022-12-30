cmake_minimum_required(VERSION 3.12)
project(bench)

include(FetchContent)
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG 361e8d1cfe0c6c36d30b39f1b61302ece5507320)
FetchContent_MakeAvailable(googlebenchmark)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Suppressing benchmark's tests" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Suppressing benchmark's install" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Suppressing benchmark's gtest tests" FORCE)
set(BENCHMARK_ENABLE_EXCEPTIONS OFF CACHE BOOL "Suppressing benchmark's exceptions" FORCE)

add_executable(bench bench.cpp)
target_link_libraries(bench benchmark::benchmark benchmark::benchmark_main src)
