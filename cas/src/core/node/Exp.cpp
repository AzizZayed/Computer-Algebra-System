//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Exp.h"
#include "cas/node/Const.h"
#include "cas/node/Log.h"
#include "cas/node/Product.h"
#include "fmt/format.h"

CAS_NAMESPACE

Exp::Exp(Expression* exponent)
    : Power({ExpressionType::EXPONENTIAL, "exponential", "exp"}, Const::E(), exponent) {}

double Exp::evaluate(const VariableMap& variables) {
    return std::exp(exponent->evaluate(variables));
}

Exp* Exp::clone() {
    return new Exp(exponent->clone());
}

Expression* Exp::_derivative(char var) {
    if (exponent->isOfType(ExpressionType::CONSTANT)) {
        return new Const;
    }

    return clone()->multiply(exponent->derivative(var));
}

Expression* Exp::simplified() {
    if (exponent->isOfType(ExpressionType::CONSTANT)) {
        double exponentValue = exponent->evaluate();
        if (exponentValue == 0)
            return Const::one();
        if (exponentValue == 1)
            return Const::E();
    }
    if (exponent->isOfType(ExpressionType::LOGARITHM)) {
        auto* log = dynamic_cast<Log*>(exponent);
        if (log->getBase()->equals(this->base))
            return log->getArgument()->simplified();
    }

    return exponent->simplified()->exp();
}

std::string Exp::explicitText() {
    return fmt::format("exp({})", exponent->explicitText());
}

CAS_NAMESPACE_END
