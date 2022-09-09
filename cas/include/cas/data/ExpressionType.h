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
    SQUARE_ROOT,
    CUBE_ROOT,
    ROOT,
    LOGARITHM,
    NATURAL_LOGARITHM,
    ABSOLUTE_VALUE,
    FLOOR,
    CEIL,
    ROUND,
    SIGN,
    MODULO,
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
    MIN,
    MAX,
    PRODUCT,
    SUM,
    DIVIDE,
    NEGATE,
};

CAS_NAMESPACE_END

#endif//CAS_EXPRESSIONTYPE_H
