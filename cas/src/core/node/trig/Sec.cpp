//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Sec.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
#include "cas/node/trig/Tan.h"

CAS_NAMESPACE

Sec::Sec(Expression* argument) : TrigExpression({ExpressionType::SEC, "secant", "sec"}, argument) {}

double Sec::evaluate(const std::unordered_map<char, double>& variables) {
    return 1.0 / std::cos(argument->evaluate(variables));
}

Sec* Sec::clone() {
    return new Sec(argument->clone());
}

Expression* Sec::_derivative(char variable) {
    return new Product({argument->clone()->sec(),
                        argument->clone()->tan(),
                        argument->derivative(variable)});
}

Expression* Sec::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value)) {
            Expression* cos = unitCircle[value].cos;
            return cos->clone()->reciprocal();
        }
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->simplified()->sec()->negate();
    }
    if (argument->isOfType(ExpressionType::TAN)) {
        auto* tan = dynamic_cast<Tan*>(argument);
        return tan->getArgument()->simplified()->sec();
    }

    return argument->simplified()->sec();
}

CAS_NAMESPACE_END