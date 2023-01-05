//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Sec.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Prod.h"
#include "cas/node/trig/Tan.h"

CAS_NAMESPACE

Sec::Sec(const ExprPtr& argument) : TrigExpression({ExpressionType::SEC, "secant", "sec"}, argument) {}

double Sec::evaluate(const VariableMap& variables) {
    return 1.0 / std::cos(argument->evaluate(variables));
}

ExprPtr Sec::clone() {
    return Sec::from(argument->clone());
}

ExprPtr Sec::_derivative(char variable) {
    return Prod::from({argument->clone()->sec(),
                       argument->clone()->tan(),
                       argument->derivative(variable)});
}

ExprPtr Sec::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value)) {
            ExprPtr cos = unitCircle.at(value).cos;
            return cos->clone()->reciprocal();
        }
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument.get());
        return negate->getArgument()->simplified()->sec()->negate();
    }
    if (argument->isOfType(ExpressionType::TAN)) {
        auto* tan = dynamic_cast<Tan*>(argument.get());
        return tan->getArgument()->simplified()->sec();
    }

    return argument->simplified()->sec();
}

CAS_NAMESPACE_END
