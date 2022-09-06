//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/Sign.h"
#include "core/node/Const.h"

CAS_NAMESPACE

Sign::Sign(Expression* argument)
    : FixedInputFunction({ExpressionType::SIGN, "sign", "sign"}, argument) {}

double Sign::evaluate(const std::unordered_map<char, double>& variables) {
    double eval = argument->evaluate(variables);
    return eval > 0 ? 1 : eval < 0 ? -1
                                   : 0;
}

bool Sign::equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->isOfType(ExpressionType::SIGN)) {
        auto* sign = dynamic_cast<Sign*>(expression);
        return argument->equals(sign->argument);
    }
    return false;
}

Sign* Sign::clone() {
    return new Sign(argument->clone());
}

Expression* Sign::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    }
    return this;
}

CAS_NAMESPACE_END