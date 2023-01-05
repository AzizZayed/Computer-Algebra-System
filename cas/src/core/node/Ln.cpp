//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#include "cas/node/Ln.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Exp.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Ln::Ln(const ExprPtr& argument)
    : Log({ExpressionType::NATURAL_LOGARITHM, "natural_logarithm", "ln"}, Const::E(), argument) {}

double Ln::evaluate(const VariableMap& variables) {
    return std::log(argument->evaluate(variables));
}

bool Ln::_equals(const ExprPtr& expression) {
    if (expression->isOfType(ExpressionType::NATURAL_LOGARITHM)) {
        auto* ln = dynamic_cast<Ln*>(expression.get());
        return argument->equals(ln->argument);
    }
    return false;
}

ExprPtr Ln::clone() {
    return Ln::from(argument->clone());
}

ExprPtr Ln::_derivative(char var) {
    return argument->derivative(var)->divide(argument->clone());
}

ExprPtr Ln::simplified() {
    if (argument->equals(base))
        return Const::one();
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double argumentValue = argument->evaluate();
        if (argumentValue == 1)
            return Const::zero();
    }
    if (argument->isOfType(ExpressionType::EXPONENTIAL)) {
        auto* exp = dynamic_cast<Exp*>(argument.get());
        return exp->getExponent()->simplified();
    }
    if (argument->isOfType(ExpressionType::POWER)) {
        auto* power = dynamic_cast<Power*>(argument.get());
        if (power->getBase()->equals(base))
            return power->getExponent()->simplified();
    }

    return argument->simplified()->ln();
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