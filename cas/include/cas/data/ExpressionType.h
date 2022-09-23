//
// Created by Abd-El-Aziz Zayed on 2022-08-29.
//

#ifndef CAS_EXPRESSIONTYPE_H
#define CAS_EXPRESSIONTYPE_H

#include "cas/CAS.h"
#include <cstdint>
#include <string>

CAS_NAMESPACE

enum class ExpressionType : uint16_t {
    CONSTANT = 0,
    VARIABLE,
    POWER,
    EXPONENTIAL,
    LOGARITHM,
    NATURAL_LOGARITHM,
    ROOT,
    SQUARE_ROOT,
    CUBE_ROOT,
    ABSOLUTE_VALUE,
    FLOOR,
    CEIL,
    ROUND,
    SIN,
    COS,
    TAN,
    COT,
    SEC,
    CSC,
    ARC_SIN,
    ARC_COS,
    ARC_TAN,
    ARC_COT,
    ARC_SEC,
    ARC_CSC,
    SIGN,
    MODULO,
    MIN,
    MAX,
    NEGATE,
    DIVIDE,
    PRODUCT,
    SUM,
};

CAS_NAMESPACE_END

#endif//CAS_EXPRESSIONTYPE_H
