//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Sign.h"
#include "cas/node/Const.h"
#include "cas/node/Log.h"
#include "cas/node/Negate.h"
#include "fmt/printf.h"

CAS_NAMESPACE

Sign::Sign(const ExprPtr& argument)
    : UnaryExpression({ExpressionType::SIGN, "sign", "sign"}, argument) {}

double Sign::evaluate(const VariableMap& variables) {
    double eval = argument->evaluate(variables);
    return eval > 0 ? 1 : eval < 0 ? -1
                                   : 0;
}

bool Sign::_equals(const ExprPtr& expression) {
    if (this == expression.get())
        return true;

    if (expression->isOfType(ExpressionType::SIGN)) {
        auto* sign = dynamic_cast<Sign*>(expression.get());
        return argument->equals(sign->argument);
    }
    return false;
}

ExprPtr Sign::clone() {
    return Sign::from(argument->clone());
}

ExprPtr Sign::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expr::evaluate());
    }
    if (argument->isOfType(ExpressionType::SIGN)) {
        return argument->simplified();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument.get());
        return negate->getArgument()->simplified()->sign()->negate();
    }
    return argument->simplified()->sign();
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