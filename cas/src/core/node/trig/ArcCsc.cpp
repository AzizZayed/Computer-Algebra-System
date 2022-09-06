//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/ArcCsc.h"
#include "core/node/Abs.h"
#include "core/node/Divide.h"
#include "core/node/Negate.h"
#include "core/node/Product.h"
#include "core/node/Sqrt.h"
#include "core/node/Sum.h"

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