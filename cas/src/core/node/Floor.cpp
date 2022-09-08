//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/Floor.h"
#include "core/node/Const.h"

CAS_NAMESPACE

Floor::Floor(Expression* argument)
    : BracketFunction({ExpressionType::FLOOR, "floor_value", "floor"}, argument, L"\u230A", L"\u230B", "\\lfloor", "\\rfloor") {}

double Floor::evaluate(const std::unordered_map<char, double>& variables) {
    return std::floor(argument->evaluate(variables));
}

Floor* Floor::clone() {
    return new Floor(argument->clone());
}

Expression* Floor::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        auto* constant = dynamic_cast<Const*>(argument);
        return new Const(std::floor(constant->getValue()));
    }
    return clone();// TODO: simplify
}

CAS_NAMESPACE_END
