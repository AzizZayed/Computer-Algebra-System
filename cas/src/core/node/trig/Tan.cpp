//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Tan.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/trig/ArcTan.h"
#include "cas/node/trig/Sec.h"

CAS_NAMESPACE

Tan::Tan(Expression* argument) : TrigExpression({ExpressionType::TAN, "tangent", "tan"}, argument) {}

double Tan::evaluate(const std::unordered_map<char, double>& variables) {
    return std::tan(argument->evaluate(variables));
}

Tan* Tan::clone() {
    return new Tan(argument->clone());
}

Expression* Tan::_derivative(char variable) {
    return argument->clone()
            ->sec()
            ->power(2)
            ->multiply(argument->derivative(variable));
}

Expression* Tan::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value))
            return unitCircle[value].tan->clone();
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->simplified()->tan()->negate();
    }
    if (argument->isOfType(ExpressionType::ARC_TAN)) {
        auto* arcTan = dynamic_cast<ArcTan*>(argument);
        return arcTan->getArgument()->simplified();
    }

    return argument->simplified()->tan();
}

CAS_NAMESPACE_END