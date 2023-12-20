//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Negate.h"
#include "cas/node/Const.h"
#include "fmt/format.h"

CAS_NAMESPACE

Negate::Negate(Expression* expression)
    : UnaryExpression({ExpressionType::NEGATE, "negate", "neg"}, expression) {}

double Negate::evaluate(const VariableMap& variables) {
    return -arg->evaluate(variables);
}

bool Negate::_equals(Expression* expr) {
    auto* negate = dynamic_cast<Negate*>(expr);
    return arg->equals(negate->arg);
}

Negate* Negate::clone() {
    return new Negate(arg->clone());
}

Negate* Negate::_derivative(char var) {
    return new Negate(arg->derivative(var));
}

Expression* Negate::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->arg->simplified();
    }

    return arg->simplified()->negate();
}

bool Negate::needsParentheses() {
    return arg->isOfType(ExpressionType::SUM);
}

std::string Negate::latex() {
    return "-" + arg->latex();
}

std::string Negate::str() {
    if (needsParentheses())
        return fmt::format("-({})", arg->str());
    return fmt::format("-{}", arg->str());
}

std::string Negate::text() {
    return fmt::format("(-({}))", arg->text());
}

std::string Negate::explicitText() {
    return fmt::format("neg({})", arg->explicitText());
}

CAS_NAMESPACE_END
