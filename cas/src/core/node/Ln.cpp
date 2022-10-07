//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#include "cas/node/Ln.h"
#include "cas/CAS.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Ln::Ln(Expression* argument)
    : Log({ExpressionType::NATURAL_LOGARITHM, "natural_logarithm", "ln"}, Const::E(), argument) {}

double Ln::evaluate(const std::unordered_map<char, double>& variables) {
    return std::log(argument->evaluate(variables));
}

bool Ln::_equals(Expression* expression) {
    if (expression->isOfType(ExpressionType::NATURAL_LOGARITHM)) {
        auto* ln = dynamic_cast<Ln*>(expression);
        return argument->equals(ln->argument);
    }
    return false;
}

Ln* Ln::clone() {
    return new Ln(argument->clone());
}

Expression* Ln::_derivative(char var) {
    return new Divide(argument->derivative(var), argument->clone());
}

Expression* Ln::simplified() {
    return new Ln(argument->simplified());// TODO: Simplify
}

std::string Ln::latex() {
    if (argumentNeedsParentheses())
        return fmt::sprintf(R"(\ln{\left(%s\right)})", argument->latex());
    return fmt::sprintf("\\ln{%s}", argument->latex());
}

std::wstring Ln::stringify() {
    if (argumentNeedsParentheses())
        return fmt::sprintf(L"ln(%s)", argument->stringify());
    return fmt::format(L"ln{}", argument->stringify());
}

std::string Ln::text() {
    return fmt::format("ln({})", argument->text());
}

std::string Ln::explicitText() {
    return fmt::format("ln({})", argument->explicitText());
}

CAS_NAMESPACE_END