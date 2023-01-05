//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Negate.h"
#include "cas/node/Const.h"
#include "cas/node/Operator.h"
#include "fmt/format.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Negate::Negate(const ExprPtr& expression)
    : UnaryExpression({ExpressionType::NEGATE, "negate", "neg"}, expression) {}

double Negate::evaluate(const VariableMap& variables) {
    return -argument->evaluate(variables);
}

bool Negate::_equals(const ExprPtr& expr) {
    auto* negate = dynamic_cast<Negate*>(expr.get());
    return argument->equals(negate->argument);
}

ExprPtr Negate::clone() {
    return Negate::from(argument->clone());
}

ExprPtr Negate::_derivative(char var) {
    return Negate::from(argument->derivative(var));
}

ExprPtr Negate::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        return Const::n(Expr::evaluate());
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument.get());
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

std::wstring Negate::stringify() {
    if (needsParentheses())
        return fmt::format(L"-({})", argument->stringify());
    return fmt::format(L"-{}", argument->stringify());
}

std::string Negate::text() {
    return fmt::format("(-({}))", argument->text());
}

std::string Negate::explicitText() {
    return fmt::format("neg({})", argument->explicitText());
}

CAS_NAMESPACE_END
