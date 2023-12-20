//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Round.h"
#include "cas/node/Const.h"

CAS_NAMESPACE

Round::Round(Expression* argument)
    : BracketExpression({ExpressionType::ROUND, "round", "round"}, argument,
                        "⌊", "⌋",
                        "\\lfloor", "\\rceil") {}

double Round::evaluate(const VariableMap& variables) {
    return std::round(arg->evaluate(variables));
}

Round* Round::clone() {
    return new Round(arg->clone());
}

Expression* Round::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (arg->isOfType(ExpressionType::ROUND)) {
        return arg->simplified();
    }

    return arg->simplified()->round();
}

CAS_NAMESPACE_END