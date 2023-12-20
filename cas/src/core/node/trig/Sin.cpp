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

Sin::Sin(Expression* argument)
    : TrigExpression({ExpressionType::SIN, "sine", "sin"}, argument) {}

double Sin::evaluate(const VariableMap& variables) {
    return std::sin(arg->evaluate(variables));
}

Sin* Sin::clone() {
    return new Sin(arg->clone());
}

Expression* Sin::_derivative(char variable) {
    Expression* derivative = arg->derivative(variable);
    return arg->clone()->cos()->multiply(derivative);
}

Expression* Sin::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        double value = arg->evaluate();
        if (unitCircle.contains(value))
            return unitCircle.at(value).sin->clone();
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->sin()->negate();
    }
    if (arg->isOfType(ExpressionType::ARC_SIN)) {
        auto* arcSin = dynamic_cast<ArcSin*>(arg);
        return arcSin->getArgument()->simplified();
    }

    return arg->simplified()->sin();
}

CAS_NAMESPACE_END
