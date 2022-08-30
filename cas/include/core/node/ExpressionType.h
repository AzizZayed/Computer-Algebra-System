//
// Created by Abd-El-Aziz Zayed on 2022-08-29.
//

#ifndef CAS_EXPRESSIONTYPE_H
#define CAS_EXPRESSIONTYPE_H

#include "core/CAS.h"
#include <cstdint>
#include <string>

CAS_NAMESPACE

enum class ExpressionType : uint16_t {
    CONSTANT = 0,
};

inline std::string stringifyExpressionType(ExpressionType type) {
    switch (type) {
        case ExpressionType::CONSTANT:
            return "constant";
        default:
            return "unknown";
    }
}

CAS_NAMESPACE_END

#endif //CAS_EXPRESSIONTYPE_H
