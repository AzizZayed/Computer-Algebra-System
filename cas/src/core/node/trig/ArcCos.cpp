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

ArcCos::ArcCos(const ExprPtr& argument)
    : InverseTrigExpression({ExpressionType::ARC_COS, "arccos", "acos"}, argument) {}

double ArcCos::evaluate(const VariableMap& variables) {
    return std::acos(argument->evaluate(variables));
}

ExprPtr ArcCos::clone() {
    return ArcCos::from(argument->clone());
}

ExprPtr ArcCos::_derivative(char var) {
    return argument->derivative(var)
            ->negate()
            ->divide(Const::one()
                             ->subtract(argument->clone()->power(2))
                             ->sqrt());
}

ExprPtr ArcCos::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        if (argument->evaluate() == 1)
            return Const::zero();
        if (argument->evaluate() == -1)
            return Const::PI();
    }

    return argument->simplified()->acos();
}

CAS_NAMESPACE_END