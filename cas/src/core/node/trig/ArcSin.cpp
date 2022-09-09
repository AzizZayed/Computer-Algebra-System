//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcSin.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"
#include <vector>

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
    std::vector<Expression*> terms = {new Const(1), argument->clone()->power(2)->negate()};
    return new Divide(argument->derivative(var), new Sqrt(new Sum(terms)));
}

Expression* ArcSin::simplified() {
    return new ArcSin(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END
