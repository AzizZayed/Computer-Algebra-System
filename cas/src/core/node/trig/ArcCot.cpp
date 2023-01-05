//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcCot.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Prod.h"
#include "cas/node/Sum.h"

CAS_NAMESPACE

ArcCot::ArcCot(ExprPtr argument)
    : InverseTrigExpression({ExpressionType::ARC_COT, "arccot", "acot"}, argument) {}

double ArcCot::evaluate(const VariableMap& variables) {
    return std::atan(1 / argument->evaluate(variables));
}

ExprPtr ArcCot::clone() {
    return ArcCot::from(argument->clone());
}

ExprPtr ArcCot::_derivative(char var) {
    return Divide::from(
            argument->derivative(var)->negate(),
            Sum::from({argument->clone()->power(2), Const::one()}));
}

ExprPtr ArcCot::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        if (argument->evaluate() == 1)
            return Const::PI()->divide(4);
        if (argument->evaluate() == 0)
            return Const::PI()->divide(2);
        if (argument->evaluate() == -1)
            return Const::PI()->multiply(3)->divide(4);
    }

    return argument->simplified()->acot();
}

CAS_NAMESPACE_END
