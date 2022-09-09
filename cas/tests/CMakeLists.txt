cmake_minimum_required(VERSION 3.23)
project(tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # fix windows build issue
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCE
        test_runner.cpp
        core/node/ConstantNodeTest.cpp
        core/node/VariableNodeTest.cpp
        core/node/SumNodeTest.cpp
        core/node/ProductNodeTest.cpp
        core/node/DivideNodeTest.cpp
        core/node/NegateNodeTest.cpp
        core/node/AbsNodeTest.cpp
        core/node/CbrtNodeTest.cpp
        core/node/CeilNodeTest.cpp
        core/node/ExpNodeTest.cpp
        core/node/FloorNodeTest.cpp)

add_executable(tests ${TEST_SOURCE})
target_link_libraries(tests GTest::gtest_main src)
include(GoogleTest)
gtest_discover_tests(tests)