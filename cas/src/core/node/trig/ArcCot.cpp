//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/ArcCot.h"
#include "core/node/Const.h"
#include "core/node/Divide.h"
#include "core/node/Negate.h"
#include "core/node/Power.h"
#include "core/node/Sum.h"

CAS_NAMESPACE

ArcCot::ArcCot(Expression* argument)
    : InverseTrigFunction({ExpressionType::ARC_COT, "arccot", "acot"}, argument) {}

double ArcCot::evaluate(const std::unordered_map<char, double>& variables) {
    return std::atan(1 / argument->evaluate(variables));
}

ArcCot* ArcCot::clone() {
    return new ArcCot(argument->clone());
}

Expression* ArcCot::derivative(char var) {
    return new Divide(
            argument->derivative(var)->negate(),
            new Sum({argument->clone()->power(2), new Const(1)}));
}

Expression* ArcCot::simplified() {
    return new ArcCot(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END
