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
    : InverseTrigFunction({ExpressionType::ARC_CSC, "arccsc", "acsc"}, argument) {}

double ArcCsc::evaluate(const std::unordered_map<char, double>& variables) {
    return std::asin(1 / argument->evaluate(variables));
}

ArcCsc* ArcCsc::clone() {
    return new ArcCsc(argument->clone());
}

Expression* ArcCsc::derivative(char var) {
    return new Divide(
            argument->derivative(var)->negate(),// new Negate(argument->derivative(var))
            new Product({argument->clone()->abs(),
                         new Sqrt(new Sum({argument->clone()->power(2),
                                           new Negate(new Const(1))}))}));
}

Expression* ArcCsc::simplified() {
    return new ArcCsc(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END