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
    : InverseTrigFunction({ExpressionType::ARC_SEC, "arcsec", "asec"}, argument) {}

double ArcSec::evaluate(const std::unordered_map<char, double>& variables) {
    return std::acos(1.0 / argument->evaluate(variables));
}

ArcSec* ArcSec::clone() {
    return new ArcSec(argument->clone());
}

Expression* ArcSec::derivative(char var) {
    return new Divide(
            argument->derivative(var),
            new Product({argument->clone()->abs(),
                         new Sqrt(new Sum({argument->clone()->power(2),
                                           new Negate(new Const(1))}))}));
}

Expression* ArcSec::simplified() {
    return new ArcSec(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END