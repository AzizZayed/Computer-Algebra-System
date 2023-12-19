//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Round.h"
#include "cas/node/Const.h"

CAS_NAMESPACE

Round::Round(const ExprPtr& argument)
    : BracketExpression({ExpressionType::ROUND, "round", "round"}, argument, L"\u230A", L"\u2309", "\\lfloor", "\\rceil") {}

double Round::evaluate(const VariableMap& variables) {
    return std::round(argument->evaluate(variables));
}

ExprPtr Round::clone() {
    return Round::from(argument->clone());
}

ExprPtr Round::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expr::evaluate());
    }
    if (argument->isOfType(ExpressionType::ROUND)) {
        return argument->simplified();
    }

    return argument->simplified()->round();
}

CAS_NAMESPACE_END