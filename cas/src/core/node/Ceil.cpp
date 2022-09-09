//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Ceil.h"
#include "cas/node/Const.h"

CAS_NAMESPACE

Ceil::Ceil(Expression* argument)
    : BracketFunction({ExpressionType::CEIL, "ceiling", "ceil"}, argument, L"\u2308", L"\u2309", "\\lceil", "\\rceil") {}

double Ceil::evaluate(const std::unordered_map<char, double>& variables) {
    return std::ceil(argument->evaluate(variables));
}

Ceil* Ceil::clone() {
    return new Ceil(argument->clone());
}

Expression* Ceil::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        auto* constant = dynamic_cast<Const*>(argument);
        return new Const(std::ceil(constant->getValue()));
    }
    return clone();// TODO: simplify
}

CAS_NAMESPACE_END
