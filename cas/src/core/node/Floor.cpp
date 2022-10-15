//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Floor.h"
#include "cas/node/Ceil.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"

CAS_NAMESPACE

Floor::Floor(Expression* argument)
    : BracketExpression({ExpressionType::FLOOR, "floor_value", "floor"}, argument, L"\u230A", L"\u230B", "\\lfloor", "\\rfloor") {}

double Floor::evaluate(const std::unordered_map<char, double>& variables) {
    return std::floor(argument->evaluate(variables));
}

Floor* Floor::clone() {
    return new Floor(argument->clone());
}

Expression* Floor::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (argument->isOfType(ExpressionType::FLOOR)) {
        return argument->simplified();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->simplified()->ceil()->negate();
    }

    // TODO floor(x + a) = floor(x) + a
    // TODO floor(x - a) = floor(x) - a

    return argument->simplified()->floor();
}

CAS_NAMESPACE_END
