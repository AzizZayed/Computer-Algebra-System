cmake_minimum_required(VERSION 3.0)
project(src)

include(FetchContent)
FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG f88fd7737de3e640c61703eb57a0fa0ce00c60cd)
FetchContent_MakeAvailable(cpr) # The commit hash for latest

set(CAS_SRC_HEADERS
        ../include/cas/CAS.h
        ../include/cas/node/IRepresentableMath.h
        ../include/cas/node/Expression.h
        ../include/cas/node/Const.h
        ../include/cas/data/ExpressionType.h
        ../include/cas/node/Var.h
        ../include/cas/node/Operator.h
        ../include/cas/node/Sum.h
        ../include/cas/node/Product.h
        ../include/cas/node/Divide.h
        ../include/cas/node/Power.h
        ../include/cas/node/Negate.h
        ../include/cas/node/Log.h
        ../include/cas/node/Ln.h
        ../include/cas/node/Exp.h
        ../include/cas/node/UnaryExpression.h
        ../include/cas/node/NaryExpression.h
        ../include/cas/node/Min.h
        ../include/cas/node/Max.h
        ../include/cas/node/BracketExpression.h
        ../include/cas/node/Abs.h
        ../include/cas/node/Floor.h
        ../include/cas/node/Ceil.h
        ../include/cas/node/Round.h
        ../include/cas/node/Mod.h
        ../include/cas/node/Sign.h
        ../include/cas/node/trig/TrigExpression.h
        ../include/cas/node/trig/Cos.h
        ../include/cas/node/trig/Sin.h
        ../include/cas/node/trig/Tan.h
        ../include/cas/node/trig/Sec.h
        ../include/cas/node/trig/Csc.h
        ../include/cas/node/trig/Cot.h
        ../include/cas/node/trig/InverseTrigExpression.h
        ../include/cas/node/trig/ArcCos.h
        ../include/cas/node/Sqrt.h
        ../include/cas/node/Root.h
        ../include/cas/node/Cbrt.h
        ../include/cas/node/trig/ArcSin.h
        ../include/cas/node/trig/ArcTan.h
        ../include/cas/node/trig/ArcSec.h
        ../include/cas/node/trig/ArcCot.h
        ../include/cas/node/trig/ArcCsc.h
        ../include/cas/util/StringUtils.h
        ../include/cas/plot/Function.h
        ../include/cas/node/IMath.h
        ../include/cas/latex/LatexRenderer.h
        ../include/cas/data/ExpressionParser.h)

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
        core/node/NaryExpression.cpp
        core/node/Min.cpp
        core/node/Max.cpp
        core/node/BracketExpression.cpp
        core/node/Abs.cpp
        core/node/Floor.cpp
        core/node/Ceil.cpp
        core/node/Round.cpp
        core/node/UnaryExpression.cpp
        core/node/Mod.cpp
        core/node/Sign.cpp
        core/node/trig/TrigExpression.cpp
        core/node/trig/Cos.cpp
        core/node/trig/Sin.cpp
        core/node/trig/Tan.cpp
        core/node/trig/Sec.cpp
        core/node/trig/Csc.cpp
        core/node/trig/Cot.cpp
        core/node/Root.cpp
        core/node/Sqrt.cpp
        core/node/Cbrt.cpp
        core/node/trig/ArcCos.cpp
        core/node/trig/ArcSin.cpp
        core/node/trig/ArcTan.cpp
        core/node/trig/ArcSec.cpp
        core/node/trig/ArcCot.cpp
        core/node/trig/ArcCsc.cpp
        core/node/trig/InverseTrigExpression.cpp
        core/data/ExpressionProperties.cpp
        core/latex/LatexRenderer.cpp
        core/plot/Function.cpp
        core/data/ExpressionParser.cpp)

add_library(${PROJECT_NAME} ${CAS_SRC_HEADERS} ${CAS_SRC_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
target_link_libraries(${PROJECT_NAME} PUBLIC cpr::cpr)