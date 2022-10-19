//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcCot.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/Sum.h"

CAS_NAMESPACE

ArcCot::ArcCot(Expression* argument)
    : InverseTrigExpression({ExpressionType::ARC_COT, "arccot", "acot"}, argument) {}

double ArcCot::evaluate(const std::unordered_map<char, double>& variables) {
    return std::atan(1 / argument->evaluate(variables));
}

ArcCot* ArcCot::clone() {
    return new ArcCot(argument->clone());
}

Expression* ArcCot::_derivative(char var) {
    return new Divide(
            argument->derivative(var)->negate(),
            new Sum({argument->clone()->power(2), new Const(1)}));
}

Expression* ArcCot::simplified() {
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
