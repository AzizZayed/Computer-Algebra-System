//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/Sec.h"
#include "core/node/Const.h"
#include "core/node/Negate.h"
#include "core/node/Product.h"
#include "core/node/trig/Tan.h"

CAS_NAMESPACE

Sec::Sec(Expression* argument) : TrigFunction({ExpressionType::SEC, "secant", "sec"}, argument) {}

double Sec::evaluate(const std::unordered_map<char, double>& variables) {
    return 1.0 / std::cos(argument->evaluate(variables));
}

Sec* Sec::clone() {
    return new Sec(argument->clone());
}

Expression* Sec::derivative(char variable) {
    return new Product({argument->clone()->sec(),
                        argument->clone()->tan(),
                        argument->derivative(variable)});
}

Expression* Sec::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    } else if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return new Sec(negate->getArgument()->clone());
    }
    return clone();// TODO: Simplify further
}

CAS_NAMESPACE_END