//
// Created by Abd-El-Aziz Zayed on 2022-09-10.
//

#ifndef CAS_IMATH_H
#define CAS_IMATH_H

#include "cas/CAS.h"

CAS_NAMESPACE

class IMath {
public:
    virtual double evaluate(const VarMap& variables) = 0;
    virtual IMath* derivative(char var) = 0;
    virtual IMath* simplified() = 0;
    virtual bool isEquivalent(IMath* expr) = 0;
};

CAS_NAMESPACE_END

#endif//CAS_IMATH_H
