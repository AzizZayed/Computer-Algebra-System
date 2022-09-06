//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/Cbrt.h"
#include "core/node/Divide.h"
#include "core/node/Product.h"

CAS_NAMESPACE

Cbrt::Cbrt(Expression* base)
    : Root({ExpressionType::CUBE_ROOT, "cube_root", "cbrt"}, base, new Const(3)) {}

double Cbrt::evaluate(const std::unordered_map<char, double>& variables) {
    return cbrt(base->evaluate(variables));
}

Cbrt* Cbrt::clone() {
    return new Cbrt(base->clone());
}

Expression* Cbrt::derivative(char var) {
    return new Divide(
            base->derivative(var),
            new Product({new Const(3), new Cbrt(new Power(base->clone(), 2))}));
}

Expression* Cbrt::simplified() {
    auto* exp = new Const(0);
    if (base->equals(exp)) {
        return exp;
    }

    return new Cbrt(base->simplified());
}

std::string Cbrt::latex() {
    return "\\sqrt[3]{" + base->latex() + "}";
}

std::string Cbrt::stringify() {
    return properties.getShortName() + "(" + base->stringify() + ")";
}

std::string Cbrt::text() {
    return properties.getShortName() + "(" + base->text() + ")";
}

std::string Cbrt::explicitText() {
    return properties.getShortName() + "(" + base->explicitText() + ")";
}

CAS_NAMESPACE_END