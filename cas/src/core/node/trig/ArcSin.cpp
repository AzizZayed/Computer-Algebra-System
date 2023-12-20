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
    return std::asin(arg->evaluate(variables));
}

ArcSin* ArcSin::clone() {
    return new ArcSin(arg->clone());
}

Expression* ArcSin::_derivative(char var) {
    std::vector<Expression*> terms = {new Const(1), arg->clone()->power(2)->negate()};
    return new Divide(arg->derivative(var), new Sqrt(new Sum(terms)));
}

Expression* ArcSin::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        if (arg->evaluate() == 0)
            return Const::zero();
        if (arg->evaluate() == 1)
            return Const::PI()->divide(2);
        if (arg->evaluate() == -1)
            return Const::PI()->negate()->divide(2);
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        return arg->simplified()->asin()->negate();
    }

    return arg->simplified()->asin();
}

CAS_NAMESPACE_END
