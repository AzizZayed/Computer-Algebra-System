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
                        "⌈", "⌉",
                        "\\lceil", "\\rceil") {}

double Ceil::evaluate(const VariableMap& variables) {
    return std::ceil(arg->evaluate(variables));
}

Ceil* Ceil::clone() {
    return new Ceil(arg->clone());
}

Expression* Ceil::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (arg->isOfType(ExpressionType::CEIL)) {
        return arg->simplified();
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->floor()->negate();
    }

    // TODO ceil(x + a) = ceil(x) + a
    // TODO ceil(x - a) = ceil(x) - a

    return arg->simplified()->ceil();
}

CAS_NAMESPACE_END
