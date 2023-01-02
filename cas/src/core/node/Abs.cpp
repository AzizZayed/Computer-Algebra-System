//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Abs.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

Abs::Abs(Expression* argument)
    : BracketExpression({ExpressionType::ABSOLUTE_VALUE, "absolute_value", "abs"}, argument, L"|", L"|", "\\left|", "\\right|") {}

double Abs::evaluate(const VariableMap& variables) {
    return std::abs(argument->evaluate(variables));
}

Abs* Abs::clone() {
    return new Abs(argument->clone());
}

Expression* Abs::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->abs();
    }
    if (argument->isOfType(ExpressionType::ABSOLUTE_VALUE)) {
        return argument->simplified();
    }

    return argument->simplified()->abs();
}

std::string Abs::text() {
    return toString(openBracket) + argument->text() + toString(closeBracket);
}

CAS_NAMESPACE_END
