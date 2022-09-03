//
// Created by Abd-El-Aziz Zayed on 2022-08-27.
//

#ifndef CAS_I_MATH_NODE_H
#define CAS_I_MATH_NODE_H

#include <string>
#include "core/CAS.h"

CAS_NAMESPACE

class IMathNode {
public:
    virtual std::string latex() = 0; // latex representation
    virtual std::string stringify() = 0; // fancy string representation
    virtual std::string text() = 0; // plain short text representation
    virtual std::string explicitText() = 0; // explicit text representation (constructor notation)
};

CAS_NAMESPACE_END

#endif //CAS_I_MATH_NODE_H
