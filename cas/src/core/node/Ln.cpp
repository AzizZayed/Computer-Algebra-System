//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#include "cas/node/Ln.h"
#include "cas/CAS.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"

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
        return "\\ln{\\left(" + argument->latex() + "\\right)}";
    return "\\ln{" + argument->latex() + "}";
}

std::wstring Ln::stringify() {
    if (argumentNeedsParentheses())
        return L"ln(" + argument->stringify() + L")";
    return L"ln" + argument->stringify();
}

std::string Ln::text() {
    return "ln(" + argument->text() + ")";
}

std::string Ln::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END