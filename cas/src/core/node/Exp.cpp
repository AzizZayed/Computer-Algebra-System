//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "core/node/Exp.h"
#include "core/CAS.h"
#include "core/node/Constant.h"
#include "core/node/Expression.h"
#include "core/node/Product.h"

CAS_NAMESPACE

Exp::Exp(Expression *exponent)
    : Power({ExpressionType::EXPONENTIAL, "exponential", "exp"}, Constant::E(), exponent) {}

double Exp::evaluate(const std::unordered_map<char, double> &variables) {
    return exp(exponent->evaluate(variables));
}

Exp *Exp::clone() {
    return new Exp(exponent->clone());
}

Expression *Exp::derivative(char var) {
    return new Product({clone(), exponent->derivative(var)});
}

Expression *Exp::simplified() {
    return new Exp(exponent->simplified());// TODO: Simplify
}

CAS_NAMESPACE_END
