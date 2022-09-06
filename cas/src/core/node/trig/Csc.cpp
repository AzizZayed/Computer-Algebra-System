//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/Csc.h"
#include "core/node/Const.h"
#include "core/node/Negate.h"
#include "core/node/Product.h"
#include "core/node/trig/Cot.h"
#include <cmath>

CAS_NAMESPACE

Csc::Csc(Expression* argument) : TrigFunction({ExpressionType::CSC, "cosecant", "csc"}, argument) {}

double Csc::evaluate(const std::unordered_map<char, double>& variables) {
    return 1.0 / std::sin(argument->evaluate(variables));
}

Csc* Csc::clone() {
    return new Csc(argument->clone());
}

Expression* Csc::derivative(char variable) {
    return new Negate(
            new Product({argument->clone()->csc(),
                         argument->clone()->cot(),
                         argument->derivative(variable)}));
}

Expression* Csc::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    }
    return clone();// TODO: Simplify further
}

CAS_NAMESPACE_END