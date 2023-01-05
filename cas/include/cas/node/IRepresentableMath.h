//
// Created by Abd-El-Aziz Zayed on 2022-08-27.
//

#ifndef CAS_INTERFACE_REPRESENTABLE_MATH_H
#define CAS_INTERFACE_REPRESENTABLE_MATH_H

#include "cas/CAS.h"
#include <string>

CAS_NAMESPACE

class IRepresentableMath {
public:
    virtual std::string latex() = 0;       // latex representation
    virtual std::wstring stringify() = 0;  // fancy string representation
    virtual std::string text() = 0;        // plain short text representation
    virtual std::string explicitText() = 0;// explicit text representation (constructor notation)
};

CAS_NAMESPACE_END

#endif//CAS_INTERFACE_REPRESENTABLE_MATH_H
