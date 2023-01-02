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
    return std::atan(argument->evaluate(variables));
}

ArcTan* ArcTan::clone() {
    return new ArcTan(argument->clone());
}

Expression* ArcTan::_derivative(char var) {
    return new Divide(
            argument->derivative(var),
            new Sum({new Const(1), argument->clone()->power(2)}));
}

Expression* ArcTan::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        if (argument->evaluate() == 0)
            return Const::zero();
        if (argument->evaluate() == 1)
            return Const::PI()->divide(4);
        if (argument->evaluate() == -1)
            return Const::PI()->negate()->divide(4);
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        return argument->simplified()->atan()->negate();
    }

    return argument->simplified()->atan();
}

CAS_NAMESPACE_END