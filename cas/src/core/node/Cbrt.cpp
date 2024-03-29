//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Cbrt.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Product.h"
#include <fmt/printf.h>

CAS_NAMESPACE

Cbrt::Cbrt(Expression* base)
    : Root({ExpressionType::CUBE_ROOT, "cube_root", "cbrt"}, base, new Const(3)) {}

double Cbrt::evaluate(const VariableMap& variables) {
    return std::cbrt(base->evaluate(variables));
}

Cbrt* Cbrt::clone() {
    return new Cbrt(base->clone());
}

Expression* Cbrt::_derivative(char var) {
    if (base->isOfType(ExpressionType::CONSTANT)) {
        return new Const(0);
    }

    return base->derivative(var)
            ->divide(Const::n(3)
                             ->multiply(base->clone()
                                                ->power(2)
                                                ->cbrt()));
}

Expression* Cbrt::simplified() {
    if (base->isOfType(ExpressionType::CONSTANT)) {
        double cbrt = Expression::evaluate();
        if (isWholeNumber(cbrt))
            return new Const(cbrt);
        return clone();
    }
    if (base->isOfType(ExpressionType::POWER)) {
        auto* power = dynamic_cast<Power*>(base);
        if (power->getExponent()->isOfType(ExpressionType::CONSTANT)) {
            double exponent = power->getExponent()->evaluate();
            if (exponent == 3)
                return power->getBase()->simplified();
        }
    }

    return base->simplified()->cbrt();
}

std::string Cbrt::latex() {
    return fmt::sprintf("\\sqrt[3]{%s}", base->latex());
}

std::string Cbrt::str() {
    return fmt::format("{}({})", properties.getShortName(), base->str());
}

std::string Cbrt::text() {
    return properties.getShortName() + "(" + base->text() + ")";
}

std::string Cbrt::explicitText() {
    return properties.getShortName() + "(" + base->explicitText() + ")";
}

CAS_NAMESPACE_END