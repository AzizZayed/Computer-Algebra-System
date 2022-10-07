//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcCsc.h"
#include "cas/node/Abs.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"

CAS_NAMESPACE

ArcCsc::ArcCsc(Expression* argument)
    : InverseTrigExpression({ExpressionType::ARC_CSC, "arccsc", "acsc"}, argument) {}

double ArcCsc::evaluate(const std::unordered_map<char, double>& variables) {
    return std::asin(1 / argument->evaluate(variables));
}

ArcCsc* ArcCsc::clone() {
    return new ArcCsc(argument->clone());
}

Expression* ArcCsc::_derivative(char var) {

    return argument->derivative(var)
            ->negate()
            ->divide(argument->clone()
                             ->abs()
                             ->multiply(argument->clone()
                                                ->power(2)
                                                ->subtract(1)
                                                ->sqrt()));
}

Expression* ArcCsc::simplified() {
    return new ArcCsc(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END