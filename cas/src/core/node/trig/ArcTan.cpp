//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcTan.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Sum.h"

CAS_NAMESPACE

ArcTan::ArcTan(Expression* argument)
    : InverseTrigExpression({ExpressionType::ARC_TAN, "arctan", "atan"}, argument) {}

double ArcTan::evaluate(const VariableMap& variables) {
    return std::atan(arg->evaluate(variables));
}

ArcTan* ArcTan::clone() {
    return new ArcTan(arg->clone());
}

Expression* ArcTan::_derivative(char var) {
    return new Divide(
            arg->derivative(var),
            new Sum({new Const(1), arg->clone()->power(2)}));
}

Expression* ArcTan::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        if (arg->evaluate() == 0)
            return Const::zero();
        if (arg->evaluate() == 1)
            return Const::PI()->divide(4);
        if (arg->evaluate() == -1)
            return Const::PI()->negate()->divide(4);
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        return arg->simplified()->atan()->negate();
    }

    return arg->simplified()->atan();
}

CAS_NAMESPACE_END