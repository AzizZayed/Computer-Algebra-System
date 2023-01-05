//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Csc.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Prod.h"
#include "cas/node/trig/ArcCsc.h"
#include "cas/node/trig/Cot.h"

CAS_NAMESPACE

Csc::Csc(ExprPtr argument) : TrigExpression({ExpressionType::CSC, "cosecant", "csc"}, argument) {}

double Csc::evaluate(const VariableMap& variables) {
    return 1.0 / std::sin(argument->evaluate(variables));
}

ExprPtr Csc::clone() {
    return Csc::from(argument->clone());
}

ExprPtr Csc::_derivative(char variable) {
    return Prod::from({argument->clone()->csc(),
                       argument->clone()->cot(),
                       argument->derivative(variable)})
            ->negate();
}

ExprPtr Csc::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value)) {
            ExprPtr sin = unitCircle.at(value).sin;
            return sin->clone()->reciprocal();
        }
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument.get());
        return negate->getArgument()->simplified()->csc()->negate();
    }
    if (argument->isOfType(ExpressionType::ARC_CSC)) {
        auto* arcCsc = dynamic_cast<ArcCsc*>(argument.get());
        return arcCsc->getArgument()->simplified();
    }

    return argument->simplified()->csc();
}

CAS_NAMESPACE_END
