//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcSec.h"
#include "cas/node/Abs.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"

CAS_NAMESPACE

ArcSec::ArcSec(Expression* argument)
    : InverseTrigExpression({ExpressionType::ARC_SEC, "arcsec", "asec"}, argument) {}

double ArcSec::evaluate(const VariableMap& variables) {
    return std::acos(1.0 / argument->evaluate(variables));
}

ArcSec* ArcSec::clone() {
    return new ArcSec(argument->clone());
}

Expression* ArcSec::_derivative(char var) {
    return argument->derivative(var)
            ->divide(argument->clone()
                             ->abs()
                             ->multiply(argument->clone()
                                                ->power(2)
                                                ->subtract(1)
                                                ->sqrt()));
}

Expression* ArcSec::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        if (argument->evaluate() == 1)
            return Const::zero();
        if (argument->evaluate() == 2)
            return Const::PI()->divide(3);
        if (argument->evaluate() == -1)
            return Const::PI();
        if (argument->evaluate() == -2)
            return Const::PI()->multiply(2)->divide(3);
    }

    return argument->simplified()->asec();
}

CAS_NAMESPACE_END