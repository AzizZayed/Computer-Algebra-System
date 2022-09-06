cmake_minimum_required(VERSION 3.23)
project(src)

set(CAS_SRC_HEADERS
        ../include/core/CAS.h
        ../include/core/node/IMathNode.h
        ../include/core/node/Expression.h
        ../include/core/node/Const.h
        ../include/core/node/ExpressionType.h
        ../include/core/node/Var.h
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
        ../include/core/node/Round.h
        ../include/core/node/Mod.h
        ../include/core/node/Sign.h
        ../include/core/node/trig/TrigFunction.h
        ../include/core/node/trig/Cos.h
        ../include/core/node/trig/Sin.h
        ../include/core/node/trig/Tan.h
        ../include/core/node/trig/Sec.h
        ../include/core/node/trig/Csc.h
        ../include/core/node/trig/Cot.h
        ../include/core/node/trig/InverseTrigFunction.h ../include/core/node/trig/ArcCos.h ../include/core/node/Sqrt.h ../include/core/node/Root.h ../include/core/node/Cbrt.h ../include/core/node/trig/ArcSin.h ../include/core/node/trig/ArcTan.h ../include/core/node/trig/ArcSec.h ../include/core/node/trig/ArcCot.h ../include/core/node/trig/ArcCsc.h)

set(CAS_SRC_SOURCES
        core/node/Const.cpp
        core/node/Var.cpp
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
        core/node/FixedInputFunction.cpp
        core/node/Mod.cpp
        core/node/Sign.cpp
        core/node/trig/TrigFunction.cpp
        core/node/trig/Cos.cpp
        core/node/trig/Sin.cpp
        core/node/trig/Tan.cpp
        core/node/trig/Sec.cpp
        core/node/trig/Csc.cpp
        core/node/trig/Cot.cpp core/node/Root.cpp core/node/Sqrt.cpp core/node/Cbrt.cpp core/node/trig/ArcCos.cpp core/node/trig/ArcSin.cpp core/node/trig/ArcTan.cpp core/node/trig/ArcSec.cpp core/node/trig/ArcCot.cpp core/node/trig/ArcCsc.cpp)

add_library(${PROJECT_NAME} ${CAS_SRC_HEADERS} ${CAS_SRC_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)