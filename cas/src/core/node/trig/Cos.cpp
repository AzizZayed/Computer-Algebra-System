//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Cos.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
#include "cas/node/trig/Sin.h"

CAS_NAMESPACE

Cos::Cos(Expression* argument) : TrigFunction({ExpressionType::COS, "cosine", "cos"}, argument) {}

double Cos::evaluate(const std::unordered_map<char, double>& variables) {
    return std::cos(argument->evaluate(variables));
}

Cos* Cos::clone() {
    return new Cos(argument->clone());
}

Expression* Cos::derivative(char variable) {
    return new Negate(argument->clone()->sin()->multiply(argument->derivative(variable)));
}

Expression* Cos::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    } else if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return new Cos(negate->getArgument()->clone());
    }
    return clone();// TODO: Simplify further
}

CAS_NAMESPACE_END