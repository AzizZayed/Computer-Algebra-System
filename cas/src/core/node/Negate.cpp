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
    return -argument->evaluate(variables);
}

bool Negate::_equals(Expression* expr) {
    auto* negate = dynamic_cast<Negate*>(expr);
    return argument->equals(negate->argument);
}

Negate* Negate::clone() {
    return new Negate(argument->clone());
}

Negate* Negate::_derivative(char var) {
    return new Negate(argument->derivative(var));
}

Expression* Negate::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expression::evaluate());
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->argument->simplified();
    }

    return argument->simplified()->negate();
}

bool Negate::needsParentheses() {
    return argument->isOfType(ExpressionType::SUM);
}

std::string Negate::latex() {
    return "-" + argument->latex();
}

std::string Negate::str() {
    if (needsParentheses())
        return fmt::format("-({})", argument->str());
    return fmt::format("-{}", argument->str());
}

std::string Negate::text() {
    return fmt::format("(-({}))", argument->text());
}

std::string Negate::explicitText() {
    return fmt::format("neg({})", argument->explicitText());
}

CAS_NAMESPACE_END
