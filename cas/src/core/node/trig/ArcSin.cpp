//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcSin.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"

CAS_NAMESPACE

ArcSin::ArcSin(Expression* argument)
    : InverseTrigExpression({ExpressionType::ARC_SIN, "arcsin", "asin"}, argument) {}

double ArcSin::evaluate(const VariableMap& variables) {
    return std::asin(argument->evaluate(variables));
}

ArcSin* ArcSin::clone() {
    return new ArcSin(argument->clone());
}

Expression* ArcSin::_derivative(char var) {
    std::vector<Expression*> terms = {new Const(1), argument->clone()->power(2)->negate()};
    return new Divide(argument->derivative(var), new Sqrt(new Sum(terms)));
}

Expression* ArcSin::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        if (argument->evaluate() == 0)
            return Const::zero();
        if (argument->evaluate() == 1)
            return Const::PI()->divide(2);
        if (argument->evaluate() == -1)
            return Const::PI()->negate()->divide(2);
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        return argument->simplified()->asin()->negate();
    }

    return argument->simplified()->asin();
}

CAS_NAMESPACE_END
