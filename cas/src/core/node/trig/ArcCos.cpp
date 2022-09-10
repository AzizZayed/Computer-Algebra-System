//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/ArcCos.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"

CAS_NAMESPACE

ArcCos::ArcCos(Expression* argument)
    : InverseTrigFunction({ExpressionType::ARC_COS, "arccos", "acos"}, argument) {}

double ArcCos::evaluate(const std::unordered_map<char, double>& variables) {
    return std::acos(argument->evaluate(variables));
}

ArcCos* ArcCos::clone() {
    return new ArcCos(argument->clone());
}

Expression* ArcCos::derivative(char var) {
    if (argument->isOfType(ExpressionType::CONSTANT))
        return new Const(0);

    if (argument->isOfType(ExpressionType::VARIABLE)) {
        auto* variable = dynamic_cast<Var*>(argument);
        if (variable->getSymbol() != var)
            return new Const(0);
    }

    auto* one = new Const(1);
    return argument->derivative(var)
            ->negate()
            ->divide(one->subtract(argument->clone()->power(2))->sqrt());
}

Expression* ArcCos::simplified() {
    return new ArcCos(argument->simplified());// TODO: Simplify further
}

CAS_NAMESPACE_END