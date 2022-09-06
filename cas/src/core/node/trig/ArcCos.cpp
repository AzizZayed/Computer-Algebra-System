//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/ArcCos.h"
#include "core/node/Divide.h"
#include "core/node/Negate.h"
#include "core/node/Sqrt.h"
#include "core/node/Sum.h"

CAS_NAMESPACE

ArcCos::ArcCos(Expression* argument)
    : InverseTrigFunction({ExpressionType::ARC_COS, "arccos", "acos"}, argument) {}

double ArcCos::evaluate(const std::unordered_map<char, double>& variables) {
    return std::acos(argument->evaluate(variables));
}

ArcCos* ArcCos::clone() {
    return new ArcCos(argument->clone());
}

Expression* ArcCos::derivative(char var) {
    return new Divide(
            argument->derivative(var)->negate(),
            new Sqrt(new Sum({new Const(1),
                              new Negate(argument->clone()->power(2))})));
}

Expression* ArcCos::simplified() {
    return new ArcCos(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END