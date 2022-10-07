//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Sign.h"
#include "cas/node/Const.h"
#include "cas/node/Log.h"
#include "fmt/printf.h"

CAS_NAMESPACE

Sign::Sign(Expression* argument)
    : UnaryExpression({ExpressionType::SIGN, "sign", "sign"}, argument) {}

double Sign::evaluate(const std::unordered_map<char, double>& variables) {
    double eval = argument->evaluate(variables);
    return eval > 0 ? 1 : eval < 0 ? -1
                                   : 0;
}

bool Sign::_equals(Expression* expression) {
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

std::string Sign::latex() {
    if (needsParentheses())
        return fmt::sprintf(R"(\text{sign}{\,\left(%s\right)})", argument->latex());
    return fmt::sprintf(R"(\text{sign}{\,%s})", argument->latex());
}

bool Sign::needsParentheses() {
    return argument->isOfType(ExpressionType::SUM) || argument->isOfType(ExpressionType::PRODUCT) || argument->isOfType(ExpressionType::LOGARITHM) || argument->isOfType(ExpressionType::NATURAL_LOGARITHM) || argument->isOfType(ExpressionType::POWER) || argument->isOfType(ExpressionType::DIVIDE);
}

CAS_NAMESPACE_END