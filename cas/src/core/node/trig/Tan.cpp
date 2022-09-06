//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/Tan.h"
#include "core/node/Power.h"
#include "core/node/Product.h"
#include "core/node/trig/Sec.h"

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