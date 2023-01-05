//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcSin.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"

CAS_NAMESPACE

ArcSin::ArcSin(ExprPtr argument)
    : InverseTrigExpression({ExpressionType::ARC_SIN, "arcsin", "asin"}, argument) {}

double ArcSin::evaluate(const VariableMap& variables) {
    return std::asin(argument->evaluate(variables));
}

ExprPtr ArcSin::clone() {
    return ArcSin::from(argument->clone());
}

ExprPtr ArcSin::_derivative(char var) {
    // arcsin( f )' = f' / sqrt(1 - f^2)
    std::vector<ExprPtr> terms = {Const::one(), argument->clone()->power(2)->negate()};
    return argument->derivative(var)->divide(Sum::from(terms)->sqrt());
}

ExprPtr ArcSin::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        if (argument->evaluate() == 0)
            return Const::zero();
        if (argument->evaluate() == 1)
            return Const::PI()->divide(2);
        if (argument->evaluate() == -1)
            return Const::PI()->negate()->divide(2);
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        return argument->simplified()->asin()->negate();
    }

    return argument->simplified()->asin();
}

CAS_NAMESPACE_END
