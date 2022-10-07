//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Exp.h"
#include "cas/CAS.h"
#include "cas/node/Const.h"
#include "cas/node/Expression.h"
#include "cas/node/Product.h"
#include "fmt/format.h"

CAS_NAMESPACE

Exp::Exp(Expression* exponent)
    : Power({ExpressionType::EXPONENTIAL, "exponential", "exp"}, Const::E(), exponent) {}

double Exp::evaluate(const std::unordered_map<char, double>& variables) {
    return std::exp(exponent->evaluate(variables));
}

Exp* Exp::clone() {
    return new Exp(exponent->clone());
}

Expression* Exp::_derivative(char var) {
    if (exponent->isOfType(ExpressionType::CONSTANT)) {
        return new Const;
    }

    return new Product({clone(), exponent->derivative(var)});
}

Expression* Exp::simplified() {
    if (exponent->isOfType(ExpressionType::CONSTANT)) {
        auto* constant = dynamic_cast<Const*>(exponent);
        if (constant->getValue() == 0)
            return new Const(1);
        if (constant->getValue() == 1)
            return Const::E();
    }

    return new Exp(exponent->simplified());// TODO: Simplify
}

std::string Exp::explicitText() {
    return fmt::format("exp({})", exponent->explicitText());
}

CAS_NAMESPACE_END
