//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Cbrt.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Prod.h"
#include "cas/util/StringUtils.h"
#include <fmt/printf.h>
#include <fmt/xchar.h>

CAS_NAMESPACE

Cbrt::Cbrt(ExprPtr base)
    : Root({ExpressionType::CUBE_ROOT, "cube_root", "cbrt"}, base, Const::n(3)) {}

double Cbrt::evaluate(const VariableMap& variables) {
    return std::cbrt(base->evaluate(variables));
}

ExprPtr Cbrt::clone() {
    return std::make_shared<Cbrt>(base->clone());
}

ExprPtr Cbrt::_derivative(char var) {
    if (base->isOfType(ExpressionType::CONSTANT)) {
        return Const::zero();
    }

    return base->derivative(var)
            ->divide(Const::n(3)
                             ->multiply(base->clone()
                                                ->power(2)
                                                ->cbrt()));
}

ExprPtr Cbrt::simplified() {
    if (base->isOfType(ExpressionType::CONSTANT)) {
        double cbrt = Expr::evaluate();
        if (isWholeNumber(cbrt))
            return Const::n(cbrt);
        return clone();
    }
    if (base->isOfType(ExpressionType::POWER)) {
        auto* power = dynamic_cast<Power*>(base.get());
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

std::wstring Cbrt::stringify() {
    return fmt::format(L"{}({})", toWstring(properties.getShortName()), base->stringify());
}

std::string Cbrt::text() {
    return properties.getShortName() + "(" + base->text() + ")";
}

std::string Cbrt::explicitText() {
    return properties.getShortName() + "(" + base->explicitText() + ")";
}

CAS_NAMESPACE_END