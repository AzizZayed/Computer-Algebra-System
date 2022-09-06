//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/ArcSec.h"
#include "core/node/Abs.h"
#include "core/node/Divide.h"
#include "core/node/Negate.h"
#include "core/node/Power.h"
#include "core/node/Product.h"
#include "core/node/Sqrt.h"
#include "core/node/Sum.h"

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