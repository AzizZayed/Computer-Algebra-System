//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Cos.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Prod.h"
#include "cas/node/Sqrt.h"
#include "cas/node/trig/ArcCos.h"
#include "cas/node/trig/Sin.h"

CAS_NAMESPACE

Cos::Cos(const ExprPtr& argument) : TrigExpression({ExpressionType::COS, "cosine", "cos"}, argument) {}

double Cos::evaluate(const VariableMap& variables) {
    return std::cos(argument->evaluate(variables));
}

ExprPtr Cos::clone() {
    return Cos::from(argument->clone());
}

ExprPtr Cos::_derivative(char variable) {
    return argument->clone()
            ->sin()
            ->multiply(argument->derivative(variable))
            ->negate();
}

ExprPtr Cos::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value))
            return unitCircle.at(value).cos->clone();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument.get());
        return negate->getArgument()->simplified()->cos();
    }
    if (argument->isOfType(ExpressionType::ARC_COS)) {
        auto* arcCos = dynamic_cast<ArcCos*>(argument.get());
        return arcCos->getArgument()->simplified();
    }

    return argument->simplified()->cos();
}

CAS_NAMESPACE_END
