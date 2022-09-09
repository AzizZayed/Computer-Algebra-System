//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Cot.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/trig/Csc.h"
#include "cas/node/trig/Sec.h"

CAS_NAMESPACE

Cot::Cot(Expression* argument) : TrigFunction({ExpressionType::COT, "cotangent", "cot"}, argument) {}

double Cot::evaluate(const std::unordered_map<char, double>& variables) {
    return 1.0 / std::tan(argument->evaluate(variables));
}

Cot* Cot::clone() {
    return new Cot(argument->clone());
}

Expression* Cot::derivative(char variable) {
    return new Negate(argument->clone()
                              ->csc()
                              ->power(2)
                              ->multiply(argument->derivative(variable)));
}

Expression* Cot::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    }
    return clone();// TODO: Simplify further
}

CAS_NAMESPACE_END