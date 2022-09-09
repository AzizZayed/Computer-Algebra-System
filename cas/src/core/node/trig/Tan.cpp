//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Tan.h"
#include "cas/node/Product.h"
#include "cas/node/Const.h"

CAS_NAMESPACE

Tan::Tan(Expression* argument) : TrigFunction({ExpressionType::TAN, "tangent", "tan"}, argument) {}

double Tan::evaluate(const std::unordered_map<char, double>& variables) {
    return std::tan(argument->evaluate(variables));
}

Tan* Tan::clone() {
    return new Tan(argument->clone());
}

Expression* Tan::derivative(char variable) {
    return argument->clone()
            ->sec()
            ->power(2)
            ->multiply(argument->derivative(variable));
}

Expression* Tan::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    }
    return clone();// TODO: Simplify further
}

CAS_NAMESPACE_END