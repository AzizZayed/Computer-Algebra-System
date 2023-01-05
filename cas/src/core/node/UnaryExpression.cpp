//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/UnaryExpression.h"
#include "cas/node/Const.h"
#include "cas/node/Var.h"
#include "cas/util/StringUtils.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

UnaryExpression::UnaryExpression(const ExpressionProperties& properties, const ExprPtr& argument)
    : Expr(properties), argument(argument) {
    this->argument->setParent(this);
}

ExprPtr UnaryExpression::derivative(char var) {
    if (argument->isOfType(ExpressionType::CONSTANT))
        return Const::zero();

    if (argument->isOfType(ExpressionType::VARIABLE)) {
        auto* variable = dynamic_cast<Var*>(argument.get());
        if (variable->getSymbol() != var)
            return Const::zero();
    }

    return _derivative(var);
}

std::string UnaryExpression::latex() {
    return fmt::sprintf(R"(\%s{\left(%s\right)})", properties.getShortName(), argument->latex());
}

std::wstring UnaryExpression::stringify() {
    return fmt::format(L"{}({})", toWstring(properties.getShortName()), argument->stringify());
}

std::string UnaryExpression::text() {
    return fmt::format("{}({})", properties.getShortName(), argument->text());
}

std::string UnaryExpression::explicitText() {
    return fmt::format("{}({})", properties.getShortName(), argument->explicitText());
}

CAS_NAMESPACE_END