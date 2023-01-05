//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Tan.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Prod.h"
#include "cas/node/trig/ArcTan.h"
#include "cas/node/trig/Sec.h"

CAS_NAMESPACE

Tan::Tan(ExprPtr argument) : TrigExpression({ExpressionType::TAN, "tangent", "tan"}, argument) {}

double Tan::evaluate(const VariableMap& variables) {
    return std::tan(argument->evaluate(variables));
}

ExprPtr Tan::clone() {
    return Tan::from(argument->clone());
}

ExprPtr Tan::_derivative(char variable) {
    return argument->clone()
            ->sec()
            ->power(2)
            ->multiply(argument->derivative(variable));
}

ExprPtr Tan::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value))
            return unitCircle.at(value).tan->clone();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument.get());
        return negate->getArgument()->simplified()->tan()->negate();
    }
    if (argument->isOfType(ExpressionType::ARC_TAN)) {
        auto* arcTan = dynamic_cast<ArcTan*>(argument.get());
        return arcTan->getArgument()->simplified();
    }

    return argument->simplified()->tan();
}

CAS_NAMESPACE_END
