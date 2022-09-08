//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/Round.h"
#include "core/node/Const.h"

CAS_NAMESPACE

Round::Round(Expression* argument)
    : BracketFunction({ExpressionType::ROUND, "round", "round"}, argument, L"\u230A", L"\u2309", "\\lfloor", "\\rceil") {}

double Round::evaluate(const std::unordered_map<char, double>& variables) {
    return std::round(argument->evaluate(variables));
}

Round* Round::clone() {
    return new Round(argument->clone());
}

Expression* Round::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        auto* constant = dynamic_cast<Const*>(argument);
        return new Const(std::round(constant->getValue()));
    }
    return clone();// TODO: simplify
}

CAS_NAMESPACE_END