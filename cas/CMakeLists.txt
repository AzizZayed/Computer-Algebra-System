project("cas")

set(HEADERS
        src/core/CAS.h
        src/core/node/IMathNode.h
        src/core/node/ExpressionNode.h
        src/core/node/Constant.h)

set(SOURCES
        src/core/CAS.cpp
        src/core/node/Constant.cpp)

add_library("cas" ${HEADERS} ${SOURCES})

