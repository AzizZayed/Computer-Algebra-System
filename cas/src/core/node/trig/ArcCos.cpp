//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcCos.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"

CAS_NAMESPACE

ArcCos::ArcCos(Expression* argument)
    : InverseTrigExpression({ExpressionType::ARC_COS, "arccos", "acos"}, argument) {}

double ArcCos::evaluate(const VariableMap& variables) {
    return std::acos(arg->evaluate(variables));
}

ArcCos* ArcCos::clone() {
    return new ArcCos(arg->clone());
}

Expression* ArcCos::_derivative(char var) {
    return arg->derivative(var)
            ->negate()
            ->divide(Const::one()
                             ->subtract(arg->clone()->power(2))
                             ->sqrt());
}

Expression* ArcCos::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        if (arg->evaluate() == 1)
            return Const::zero();
        if (arg->evaluate() == -1)
            return Const::PI();
    }

    return arg->simplified()->acos();
}

CAS_NAMESPACE_END