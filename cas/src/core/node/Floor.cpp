//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Floor.h"
#include "cas/node/Ceil.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"

CAS_NAMESPACE

Floor::Floor(Expression* argument)
    : BracketExpression({ExpressionType::FLOOR, "floor_value", "floor"}, argument, "\u230A", "\u230B", "\\lfloor", "\\rfloor") {}

double Floor::evaluate(const VariableMap& variables) {
    return std::floor(arg->evaluate(variables));
}

Floor* Floor::clone() {
    return new Floor(arg->clone());
}

Expression* Floor::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (arg->isOfType(ExpressionType::FLOOR)) {
        return arg->simplified();
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->ceil()->negate();
    }

    // TODO floor(x + a) = floor(x) + a
    // TODO floor(x - a) = floor(x) - a

    return arg->simplified()->floor();
}

CAS_NAMESPACE_END
