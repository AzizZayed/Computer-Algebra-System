//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Exp.h"
#include "cas/CAS.h"
#include "cas/node/Const.h"
#include "cas/node/Expression.h"
#include "cas/node/Product.h"

CAS_NAMESPACE

Exp::Exp(Expression* exponent)
    : Power({ExpressionType::EXPONENTIAL, "exponential", "exp"}, Const::E(), exponent) {}

double Exp::evaluate(const std::unordered_map<char, double>& variables) {
    return std::exp(exponent->evaluate(variables));
}

Exp* Exp::clone() {
    return new Exp(exponent->clone());
}

Expression* Exp::derivative(char var) {
    return new Product({clone(), exponent->derivative(var)});
}

Expression* Exp::simplified() {
    return new Exp(exponent->simplified());// TODO: Simplify
}

CAS_NAMESPACE_END
