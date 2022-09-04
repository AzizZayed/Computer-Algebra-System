cmake_minimum_required(VERSION 3.23)
project(src)

set(CAS_SRC_HEADERS
        ../include/core/CAS.h
        ../include/core/node/IMathNode.h
        ../include/core/node/Expression.h
        ../include/core/node/Constant.h
        ../include/core/node/ExpressionType.h
        ../include/core/node/Variable.h
        ../include/core/node/Operator.h
        ../include/core/node/Sum.h
        ../include/core/node/Product.h
        ../include/core/node/Divide.h
        ../include/core/node/Power.h
        ../include/core/node/Negate.h
        ../include/core/node/Log.h
        ../include/core/node/Ln.h
        ../include/core/node/Exp.h)

set(CAS_SRC_SOURCES
        core/node/Constant.cpp
        core/node/Variable.cpp
        core/node/Operator.cpp
        core/node/Sum.cpp
        core/node/Product.cpp
        core/node/Divide.cpp
        core/node/Power.cpp
        core/node/Expression.cpp
        core/node/Negate.cpp
        core/node/Exp.cpp
        core/node/Log.cpp
        core/node/Ln.cpp)

add_library(${PROJECT_NAME} ${CAS_SRC_HEADERS} ${CAS_SRC_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)