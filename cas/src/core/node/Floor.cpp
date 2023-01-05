//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Floor.h"
#include "cas/node/Ceil.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"

CAS_NAMESPACE

Floor::Floor(ExprPtr argument)
    : BracketExpression({ExpressionType::FLOOR, "floor_value", "floor"}, argument, L"\u230A", L"\u230B", "\\lfloor", "\\rfloor") {}

double Floor::evaluate(const VariableMap& variables) {
    return std::floor(argument->evaluate(variables));
}

ExprPtr Floor::clone() {
    return Floor::from(argument->clone());
}

ExprPtr Floor::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expr::evaluate());
    }
    if (argument->isOfType(ExpressionType::FLOOR)) {
        return argument->simplified();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument.get());
        return negate->getArgument()->simplified()->ceil()->negate();
    }

    // TODO floor(x + a) = floor(x) + a
    // TODO floor(x - a) = floor(x) - a

    return argument->simplified()->floor();
}

CAS_NAMESPACE_END
