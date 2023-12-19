//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Cot.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Prod.h"
#include "cas/node/trig/ArcCot.h"
#include "cas/node/trig/Csc.h"
#include "cas/node/trig/Sec.h"

CAS_NAMESPACE

Cot::Cot(const ExprPtr& argument) : TrigExpression({ExpressionType::COT, "cotangent", "cot"}, argument) {}

double Cot::evaluate(const VariableMap& variables) {
    return 1.0 / std::tan(argument->evaluate(variables));
}

ExprPtr Cot::clone() {
    return Cot::from(argument->clone());
}

ExprPtr Cot::_derivative(char variable) {
    // cot( f )' = -csc( f )^2 * f'
    return argument->clone()
            ->csc()
            ->power(2)
            ->multiply(argument->derivative(variable))
            ->negate();
}

ExprPtr Cot::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value)) {
            ExprPtr tan = unitCircle.at(value).tan;
            return tan->clone()->reciprocal();
        }
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument.get());
        return negate->getArgument()->simplified()->cot()->negate();
    }
    if (argument->isOfType(ExpressionType::ARC_COT)) {
        auto* arcCot = dynamic_cast<ArcCot*>(argument.get());
        return arcCot->getArgument()->simplified();
    }

    return argument->simplified()->cot();
}

CAS_NAMESPACE_END
