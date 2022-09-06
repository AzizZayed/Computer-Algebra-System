//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/ArcSin.h"
#include "core/node/Divide.h"
#include "core/node/Negate.h"
#include "core/node/Sqrt.h"
#include "core/node/Sum.h"

CAS_NAMESPACE

ArcSin::ArcSin(Expression* argument)
    : InverseTrigFunction({ExpressionType::ARC_SIN, "arcsin", "asin"}, argument) {}

double ArcSin::evaluate(const std::unordered_map<char, double>& variables) {
    return std::asin(argument->evaluate(variables));
}

ArcSin* ArcSin::clone() {
    return new ArcSin(argument->clone());
}

Expression* ArcSin::derivative(char var) {
    return new Divide(
            argument->derivative(var),
            new Sqrt(new Sum({new Const(1),
                              argument->clone()->power(2)->negate()})));
}

Expression* ArcSin::simplified() {
    return new ArcSin(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END
