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

double Sec::evaluate(const VariableMap& variables) {
    return 1.0 / std::cos(arg->evaluate(variables));
}

Sec* Sec::clone() {
    return new Sec(arg->clone());
}

Expression* Sec::_derivative(char variable) {
    Expression* derivative = arg->derivative(variable);
    return new Product({arg->clone()->sec(), arg->clone()->tan(), derivative});
}

Expression* Sec::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        double value = arg->evaluate();
        if (unitCircle.contains(value)) {
            Expression* cos = unitCircle.at(value).cos;
            return cos->clone()->reciprocal();
        }
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->sec()->negate();
    }
    if (arg->isOfType(ExpressionType::TAN)) {
        auto* tan = dynamic_cast<Tan*>(arg);
        return tan->getArgument()->simplified()->sec();
    }

    return arg->simplified()->sec();
}

CAS_NAMESPACE_END
