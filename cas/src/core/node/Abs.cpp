//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/Abs.h"
#include "core/node/Constant.h"

CAS_NAMESPACE

Abs::Abs(Expression *argument)
    : BracketFunction({ExpressionType::ABSOLUTE_VALUE, "absolute_value", "abs"}, argument, "|", "|") {}

double Abs::evaluate(const std::unordered_map<char, double> &variables) {
    return std::abs(argument->evaluate(variables));
}

Abs *Abs::clone() {
    return new Abs(argument->clone());
}

Expression *Abs::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        auto *constant = dynamic_cast<Constant *>(argument);
        return new Constant(std::abs(constant->getValue()));
    }
    return clone();// TODO: simplify
}

CAS_NAMESPACE_END
