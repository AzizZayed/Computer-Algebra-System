//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Sign.h"
#include "cas/node/Const.h"
#include "cas/node/Log.h"
#include "cas/node/Negate.h"
#include "fmt/printf.h"

CAS_NAMESPACE

Sign::Sign(Expression* argument)
    : UnaryExpression({ExpressionType::SIGN, "sign", "sign"}, argument) {}

double Sign::evaluate(const VariableMap& variables) {
    double eval = arg->evaluate(variables);
    return eval > 0 ? 1 : eval < 0 ? -1
                                   : 0;
}

bool Sign::_equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->isOfType(ExpressionType::SIGN)) {
        auto* sign = dynamic_cast<Sign*>(expression);
        return arg->equals(sign->arg);
    }
    return false;
}

Sign* Sign::clone() {
    return new Sign(arg->clone());
}

Expression* Sign::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    }
    if (arg->isOfType(ExpressionType::SIGN)) {
        return arg->simplified();
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->sign()->negate();
    }
    return arg->simplified()->sign();
}

std::string Sign::latex() {
    if (needsParentheses())
        return fmt::sprintf(R"(\text{sign}{\,\left(%s\right)})", arg->latex());
    return fmt::sprintf(R"(\text{sign}{\,%s})", arg->latex());
}

bool Sign::needsParentheses() {
    return arg->isOfType(ExpressionType::SUM) || arg->isOfType(ExpressionType::PRODUCT) || arg->isOfType(ExpressionType::LOGARITHM) || arg->isOfType(ExpressionType::NATURAL_LOGARITHM) || arg->isOfType(ExpressionType::POWER) || arg->isOfType(ExpressionType::DIVIDE);
}

CAS_NAMESPACE_END