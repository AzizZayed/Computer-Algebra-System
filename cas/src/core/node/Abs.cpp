//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Abs.h"
#include "cas/node/Const.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

Abs::Abs(Expression* argument)
    : BracketExpression({ExpressionType::ABSOLUTE_VALUE, "absolute_value", "abs"}, argument, L"|", L"|", "\\left|", "\\right|") {}

double Abs::evaluate(const std::unordered_map<char, double>& variables) {
    return std::abs(argument->evaluate(variables));
}

Abs* Abs::clone() {
    return new Abs(argument->clone());
}

Expression* Abs::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        auto* constant = dynamic_cast<Const*>(argument);
        return new Const(std::abs(constant->getValue()));
    }
    return clone();// TODO: simplify
}

std::string Abs::text() {
    return toString(openBracket) + argument->text() + toString(closeBracket);
}

CAS_NAMESPACE_END
