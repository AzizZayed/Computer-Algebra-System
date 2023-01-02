//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Sin.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
#include "cas/node/trig/ArcSin.h"
#include "cas/node/trig/Cos.h"

CAS_NAMESPACE

Sin::Sin(Expression* argument) : TrigExpression({ExpressionType::SIN, "sinus", "sin"}, argument) {}

double Sin::evaluate(const VariableMap& variables) {
    return std::sin(argument->evaluate(variables));
}

Sin* Sin::clone() {
    return new Sin(argument->clone());
}

Expression* Sin::_derivative(char variable) {
    return argument
            ->clone()
            ->cos()
            ->multiply(argument->derivative(variable));
}

Expression* Sin::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value))
            return unitCircle.at(value).sin->clone();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->simplified()->sin()->negate();
    }
    if (argument->isOfType(ExpressionType::ARC_SIN)) {
        auto* arcSin = dynamic_cast<ArcSin*>(argument);
        return arcSin->getArgument()->simplified();
    }

    return argument->simplified()->sin();
}

CAS_NAMESPACE_END
