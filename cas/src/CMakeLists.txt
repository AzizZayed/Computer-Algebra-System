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
        ../include/core/node/Exp.h
        ../include/core/node/FixedInputFunction.h
        ../include/core/node/MultipleInputFunction.h
        ../include/core/node/Min.h
        ../include/core/node/Max.h
        ../include/core/node/BracketFunction.h
        ../include/core/node/Abs.h
        ../include/core/node/Floor.h
        ../include/core/node/Ceil.h
        ../include/core/node/Round.h ../include/core/node/Mod.h ../include/core/node/Sign.h)

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
        core/node/Ln.cpp
        core/node/MultipleInputFunction.cpp
        core/node/Min.cpp
        core/node/Max.cpp
        core/node/BracketFunction.cpp
        core/node/Abs.cpp
        core/node/Floor.cpp
        core/node/Ceil.cpp
        core/node/Round.cpp
        core/node/FixedInputFunction.cpp core/node/Mod.cpp core/node/Sign.cpp)

add_library(${PROJECT_NAME} ${CAS_SRC_HEADERS} ${CAS_SRC_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)