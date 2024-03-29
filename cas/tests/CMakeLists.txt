cmake_minimum_required(VERSION 3.12)
project(tests)

include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # fix windows build
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

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
        core/node/FloorNodeTest.cpp
        core/node/SqrtNodeTest.cpp
        core/node/PowerNodeTest.cpp
        core/node/MinNodeTest.cpp
        core/node/LnNodeTest.cpp
        core/node/RoundNodeTest.cpp
        core/node/LogNodeTest.cpp
        core/node/MaxNodeTest.cpp
        core/node/RootNodeTest.cpp
        core/node/ModNodeTest.cpp
        core/node/SignNodeTest.cpp
        core/node/SecNodeTest.cpp
        core/node/ArcCotNodeTest.cpp
        core/node/ArcCosNodeTest.cpp
        core/node/ArcSinNodeTest.cpp
        core/node/TanNodeTest.cpp
        core/node/CscNodeTest.cpp
        core/node/ArcSecNodeTest.cpp
        core/node/CotNodeTest.cpp
        core/node/CosNodeTest.cpp
        core/node/SinNodeTest.cpp
        core/node/ArcTanNodeTest.cpp
        core/node/ArcCscNodeTest.cpp
        core/util/StringUtilsTest.cpp
        core/data/ExpressionParserTest.cpp
        core/plot/FunctionTest.cpp)

add_executable(tests ${TEST_SOURCE})
target_link_libraries(tests GTest::gtest_main src)
include(GoogleTest)
gtest_discover_tests(tests)