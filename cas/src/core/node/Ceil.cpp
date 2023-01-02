//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Ceil.h"
#include "cas/node/Const.h"
#include "cas/node/Floor.h"
#include "cas/node/Negate.h"

CAS_NAMESPACE

Ceil::Ceil(Expression* argument)
    : BracketExpression({ExpressionType::CEIL, "ceiling", "ceil"}, argument,
                        L"\u2308", L"\u2309",
                        "\\lceil", "\\rceil") {}

double Ceil::evaluate(const VariableMap& variables) {
    return std::ceil(argument->evaluate(variables));
}

Ceil* Ceil::clone() {
    return new Ceil(argument->clone());
}

Expression* Ceil::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (argument->isOfType(ExpressionType::CEIL)) {
        return argument->simplified();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->simplified()->floor()->negate();
    }

    // TODO ceil(x + a) = ceil(x) + a
    // TODO ceil(x - a) = ceil(x) - a

    return argument->simplified()->ceil();
}

CAS_NAMESPACE_END
