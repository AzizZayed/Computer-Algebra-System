//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Sqrt.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Product.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

Sqrt::Sqrt(Expression* base)
    : Root({ExpressionType::SQUARE_ROOT, "square_root", "sqrt"}, base, new Const(2)) {}

double Sqrt::evaluate(const std::unordered_map<char, double>& variables) {
    return std::sqrt(base->evaluate(variables));
}

Sqrt* Sqrt::clone() {
    return new Sqrt(base->clone());
}

Expression* Sqrt::_derivative(char var) {
    return new Divide(
            base->derivative(var),
            new Product({new Const(2), clone()}));
}

Expression* Sqrt::simplified() {
    auto* exp = new Const(0);
    if (base->equals(exp)) {
        return exp;
    }

    return new Sqrt(base->simplified());
}

std::string Sqrt::latex() {
    return "\\sqrt{" + base->latex() + "}";
}

std::wstring Sqrt::stringify() {
    return toWstring(properties.getShortName()) + L"(" + base->stringify() + L")";
}

std::string Sqrt::text() {
    return properties.getShortName() + "(" + base->text() + ")";
}

std::string Sqrt::explicitText() {
    return properties.getShortName() + "(" + base->explicitText() + ")";
}

CAS_NAMESPACE_END
