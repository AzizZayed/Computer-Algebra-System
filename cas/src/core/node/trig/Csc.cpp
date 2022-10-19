//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Csc.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
#include "cas/node/trig/ArcCsc.h"
#include "cas/node/trig/Cot.h"

CAS_NAMESPACE

Csc::Csc(Expression* argument) : TrigExpression({ExpressionType::CSC, "cosecant", "csc"}, argument) {}

double Csc::evaluate(const std::unordered_map<char, double>& variables) {
    return 1.0 / std::sin(argument->evaluate(variables));
}

Csc* Csc::clone() {
    return new Csc(argument->clone());
}

Expression* Csc::_derivative(char variable) {
    return new Negate(
            new Product({argument->clone()->csc(),
                         argument->clone()->cot(),
                         argument->derivative(variable)}));
}

Expression* Csc::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value)) {
            Expression* sin = unitCircle.at(value).sin;
            return sin->clone()->reciprocal();
        }
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->simplified()->csc()->negate();
    }
    if (argument->isOfType(ExpressionType::ARC_CSC)) {
        auto* arcCsc = dynamic_cast<ArcCsc*>(argument);
        return arcCsc->getArgument()->simplified();
    }

    return argument->simplified()->csc();
}

CAS_NAMESPACE_END
