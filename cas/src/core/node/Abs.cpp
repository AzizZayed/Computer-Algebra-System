//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Abs.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"

CAS_NAMESPACE

Abs::Abs(Expression* argument)
    : BracketExpression({ExpressionType::ABSOLUTE_VALUE, "absolute_value", "abs"},
                        argument, "|", "|", "\\left|", "\\right|") {}

double Abs::evaluate(const VariableMap& variables) {
    return std::abs(arg->evaluate(variables));
}

Abs* Abs::clone() {
    return new Abs(arg->clone());
}

Expression* Abs::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->abs();
    }
    if (arg->isOfType(ExpressionType::ABSOLUTE_VALUE)) {
        return arg->simplified();
    }

    return arg->simplified()->abs();
}

std::string Abs::text() {
    return openBracket + arg->text() + closeBracket;
}

CAS_NAMESPACE_END
