//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Cos.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
#include "cas/node/Sqrt.h"
#include "cas/node/trig/ArcCos.h"
#include "cas/node/trig/Sin.h"

CAS_NAMESPACE

Cos::Cos(Expression* argument) : TrigExpression({ExpressionType::COS, "cosine", "cos"}, argument) {}

double Cos::evaluate(const VariableMap& variables) {
    return std::cos(argument->evaluate(variables));
}

Cos* Cos::clone() {
    return new Cos(argument->clone());
}

Expression* Cos::_derivative(char variable) {
    return new Negate(argument->clone()->sin()->multiply(argument->derivative(variable)));
}

Expression* Cos::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value))
            return unitCircle.at(value).cos->clone();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->simplified()->cos();
    }
    if (argument->isOfType(ExpressionType::ARC_COS)) {
        auto* arcCos = dynamic_cast<ArcCos*>(argument);
        return arcCos->getArgument()->simplified();
    }

    return argument->simplified()->cos();
}

CAS_NAMESPACE_END
