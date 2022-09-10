//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Cbrt.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Product.h"
#include "cas/util/StringUtils.h"


CAS_NAMESPACE

Cbrt::Cbrt(Expression* base)
    : Root({ExpressionType::CUBE_ROOT, "cube_root", "cbrt"}, base, new Const(3)) {}

double Cbrt::evaluate(const std::unordered_map<char, double>& variables) {
    return std::cbrt(base->evaluate(variables));
}

Cbrt* Cbrt::clone() {
    return new Cbrt(base->clone());
}

Expression* Cbrt::_derivative(char var) {
    if (base->isOfType(ExpressionType::CONSTANT)) {
        return new Const(0);
    }

    return new Divide(
            base->derivative(var),
            new Product({new Const(3), new Cbrt(new Power(base->clone(), 2))}));
}

Expression* Cbrt::simplified() {
    if (base->isOfType(ExpressionType::CONSTANT)) {
        auto* constant = dynamic_cast<Const*>(base);
        double cbrt = std::cbrt(constant->getValue());
        if (isWholeNumber(cbrt))
            return new Const(cbrt);
    }

    return new Cbrt(base->simplified());
}

std::string Cbrt::latex() {
    return "\\sqrt[3]{" + base->latex() + "}";
}

std::wstring Cbrt::stringify() {
    return toWstring(properties.getShortName()) + L"(" + base->stringify() + L")";
}

std::string Cbrt::text() {
    return properties.getShortName() + "(" + base->text() + ")";
}

std::string Cbrt::explicitText() {
    return properties.getShortName() + "(" + base->explicitText() + ")";
}

CAS_NAMESPACE_END