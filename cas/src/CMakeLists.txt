cmake_minimum_required(VERSION 3.23)
project(src)

set(CAS_SRC_HEADERS
        ../include/core/CAS.h
        ../include/core/node/IMathNode.h
        ../include/core/node/Expression.h
        ../include/core/node/Constant.h
        ../include/core/node/ExpressionType.h)

set(CAS_SRC_SOURCES
        core/CAS.cpp
        core/node/Constant.cpp)

add_library(${PROJECT_NAME} ${CAS_SRC_HEADERS} ${CAS_SRC_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)