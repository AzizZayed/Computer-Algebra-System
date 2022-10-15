//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Root.h"
#include "cas/node/Cbrt.h"
#include "cas/node/Const.h"
#include "cas/node/Sqrt.h"
#include "cas/util/StringUtils.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Root::Root(const ExpressionProperties& props, Expression* base, Expression* root)
    : Power(props, base, root) {}

Root::Root(Expression* base, Expression* root)
    : Root({ExpressionType::ROOT, "root", "root"}, base, root) {}

Root::Root(Expression* base, double root)
    : Root(base, new Const(root)) {}

double Root::evaluate(const std::unordered_map<char, double>& variables) {
    return pow(base->evaluate(variables), 1.0 / exponent->evaluate(variables));
}

Root* Root::clone() {
    return new Root(base->clone(), exponent->clone());
}

Expression* Root::simplified() {
    if (exponent->isOfType(ExpressionType::CONSTANT)) {
        double root = exponent->evaluate();
        if (root == 1)
            return base->simplified();
        if (root == 2)
            return base->simplified()->sqrt();
        if (root == 3)
            return base->simplified()->cbrt();
    }

    return new Root(base->simplified(), exponent->simplified());
}

std::string Root::latex() {
    return fmt::sprintf("\\sqrt[%s]{%s}", exponent->latex(), base->latex());
}

std::wstring Root::stringify() {
    return fmt::format(L"{}({}, {})", toWstring(properties.getShortName()), base->stringify(), exponent->stringify());
}

std::string Root::text() {
    return fmt::format("{}({}, {})", properties.getShortName(), base->text(), exponent->text());
}


CAS_NAMESPACE_END