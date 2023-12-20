//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/UnaryExpression.h"
#include "cas/node/Const.h"
#include "cas/node/Var.h"
#include "fmt/printf.h"

CAS_NAMESPACE

UnaryExpression::UnaryExpression(const ExpressionProperties& properties, Expression* argument)
    : Expression(properties), arg(argument) {
    this->arg->setParent(this);
}

UnaryExpression::~UnaryExpression() {
    delete arg;
    arg = nullptr;
}

Expression* UnaryExpression::derivative(char var) {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        return Const::zero();
    }

    if (arg->isOfType(ExpressionType::VARIABLE)) {
        auto* variable = dynamic_cast<Var*>(arg);
        if (variable->getSymbol() != var) {
            return Const::zero();
        }
    }

    return _derivative(var);
}

std::string UnaryExpression::latex() {
    return fmt::sprintf(R"(\%s{\left(%s\right)})", properties.getShortName(), arg->latex());
}

std::string UnaryExpression::str() {
    return fmt::format("{}({})", properties.getShortName(), arg->str());
}

std::string UnaryExpression::text() {
    return fmt::format("{}({})", properties.getShortName(), arg->text());
}

std::string UnaryExpression::explicitText() {
    return fmt::format("{}({})", properties.getShortName(), arg->explicitText());
}

CAS_NAMESPACE_END