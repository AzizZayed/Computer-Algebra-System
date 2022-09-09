//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Sin.h"
#include "cas/node/Const.h"
#include "cas/node/Product.h"
#include "cas/node/trig/Cos.h"

CAS_NAMESPACE

Sin::Sin(Expression* argument) : TrigFunction({ExpressionType::SIN, "sinus", "sin"}, argument) {}

double Sin::evaluate(const std::unordered_map<char, double>& variables) {
    return std::sin(argument->evaluate(variables));
}

Sin* Sin::clone() {
    return new Sin(argument->clone());
}

Expression* Sin::derivative(char variable) {
    return argument
            ->clone()
            ->cos()
            ->multiply(argument->derivative(variable));
}

Expression* Sin::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    }
    return clone();// TODO: Simplify further
}

CAS_NAMESPACE_END
