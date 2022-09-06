//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/ArcTan.h"
#include "core/node/Const.h"
#include "core/node/Divide.h"
#include "core/node/Sum.h"

CAS_NAMESPACE

ArcTan::ArcTan(Expression* argument)
    : InverseTrigFunction({ExpressionType::ARC_TAN, "arctan", "atan"}, argument) {}

double ArcTan::evaluate(const std::unordered_map<char, double>& variables) {
    return std::atan(argument->evaluate(variables));
}

ArcTan* ArcTan::clone() {
    return new ArcTan(argument->clone());
}

Expression* ArcTan::derivative(char var) {
    return new Divide(
            argument->derivative(var),
            new Sum({new Const(1), argument->clone()->power(2)}));
}

Expression* ArcTan::simplified() {
    return new ArcTan(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END