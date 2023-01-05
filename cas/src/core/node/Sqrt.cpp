//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Sqrt.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Prod.h"
#include "cas/util/StringUtils.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Sqrt::Sqrt(ExprPtr base)
    : Root({ExpressionType::SQUARE_ROOT, "square_root", "sqrt"}, base, Const::n(2)) {}

double Sqrt::evaluate(const VariableMap& variables) {
    return std::sqrt(base->evaluate(variables));
}

ExprPtr Sqrt::clone() {
    return Sqrt::from(base->clone());
}

ExprPtr Sqrt::_derivative(char var) {

    // sqrt( f )' = f' / (2 * sqrt( f ))
    return Divide::from(
            base->derivative(var),          // f'
            Const::n(2)->multiply(clone()));// 2 * sqrt( f )
}

ExprPtr Sqrt::simplified() {
    if (base->isOfType(ExpressionType::CONSTANT)) {
        double sqrt = Expr::evaluate();
        if (isWholeNumber(sqrt))
            return Const::from(sqrt);
        else
            return clone();
    }
    if (base->isOfType(ExpressionType::POWER)) {
        auto* power = dynamic_cast<Power*>(base.get());
        if (power->getExponent()->isOfType(ExpressionType::CONSTANT)) {
            double exponent = power->getExponent()->evaluate();
            if (exponent == 2)
                return power->getBase()->simplified();
        }
    }

    return base->simplified()->sqrt();
}

std::string Sqrt::latex() {
    return fmt::sprintf("\\sqrt{%s}", base->latex());
}

std::wstring Sqrt::stringify() {
    return fmt::format(L"{}({})", toWstring(properties.getShortName()), base->stringify());
}

std::string Sqrt::text() {
    return fmt::format("{}({})", properties.getShortName(), base->text());
}

std::string Sqrt::explicitText() {
    return fmt::format("{}({})", properties.getName(), base->explicitText());
}

CAS_NAMESPACE_END
