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

Cos::Cos(Expression* argument)
    : TrigExpression({ExpressionType::COS, "cosine", "cos"}, argument) {}

double Cos::evaluate(const VariableMap& variables) {
    return std::cos(arg->evaluate(variables));
}

Cos* Cos::clone() {
    return new Cos(arg->clone());
}

Expression* Cos::_derivative(char variable) {
    Expression* derivative = arg->derivative(variable);
    return new Negate(arg->clone()->sin()->multiply(derivative));
}

Expression* Cos::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        double value = arg->evaluate();
        if (unitCircle.contains(value))
            return unitCircle.at(value).cos->clone();
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->cos();
    }
    if (arg->isOfType(ExpressionType::ARC_COS)) {
        auto* arcCos = dynamic_cast<ArcCos*>(arg);
        return arcCos->getArgument()->simplified();
    }

    return arg->simplified()->cos();
}

CAS_NAMESPACE_END
