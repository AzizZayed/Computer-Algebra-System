//
// Created by Abd-El-Aziz Zayed on 2022-09-10.
//

#ifndef CAS_IMATH_H
#define CAS_IMATH_H

#include "cas/CAS.h"
#include <cmath>

CAS_NAMESPACE

class IMath {
public:
    virtual double evaluate(const VarMap& variables) = 0;
    virtual IMath* derivative(char var) = 0;
    virtual IMath* simplified() = 0;
    virtual bool isEquivalent(IMath* expr) = 0;
};

namespace math {
    const double PI = 2 * std::acos(0.0);
    const double PI_2 = PI / 2;
    const double PI_3 = PI / 3;
    const double PI_4 = PI / 4;
    const double PI_6 = PI / 6;
    const double PI_8 = PI / 8;
    const double PI_12 = PI / 12;
    const double PI_2_3 = PI_3 * 2;
    const double PI_3_4 = PI_4 * 3;
    const double PI_4_3 = PI_3 * 4;
    const double PI_5_6 = PI_6 * 5;
    const double PI_7_6 = PI_6 * 7;
    const double PI_5_4 = PI_4 * 5;
    const double PI_3_2 = PI_2 * 3;
    const double PI_5_3 = PI_3 * 5;
    const double PI_7_4 = PI_4 * 7;
    const double PI_11_6 = PI_6 * 11;

    const double E = std::exp(1.0);
    const double PHI = (1 + std::sqrt(5)) / 2;

    const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
    const double NEGATIVE_INFINITY = -POSITIVE_INFINITY;

}// namespace math

CAS_NAMESPACE_END

#endif//CAS_IMATH_H
