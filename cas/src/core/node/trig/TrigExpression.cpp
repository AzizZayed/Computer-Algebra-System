//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/TrigExpression.h"
#include "cas/node/Log.h"
#include "cas/node/Operator.h"
#include "cas/util/StringUtils.h"
#include <fmt/printf.h>
#include <fmt/xchar.h>

CAS_NAMESPACE

TrigExpression::TrigExpression(const ExpressionProperties& properties, Expression* argument)
    : UnaryExpression(properties, argument) {}

bool TrigExpression::_equals(Expression* other) {
    auto* otherTrigFunction = dynamic_cast<TrigExpression*>(other);
    return argument->equals(otherTrigFunction->argument);
}

bool TrigExpression::needsParentheses() {
    return instanceof <Operator>(argument) || instanceof <Log>(argument) || argument->isOfType(ExpressionType::POWER) || argument->isOfType(ExpressionType::DIVIDE);
}

std::string TrigExpression::latex() {
    if (needsParentheses())
        return fmt::sprintf("%s{\\left(%s\\right)}", properties.getShortName(), argument->latex());
    return fmt::sprintf("\\%s{%s}", properties.getShortName(), argument->latex());
}

std::wstring TrigExpression::stringify() {
    if (needsParentheses())
        return fmt::format(L"{} ({})", toWstring(properties.getShortName()), argument->stringify());
    return fmt::format(L"{} {}", toWstring(properties.getShortName()), argument->stringify());
}

CAS_NAMESPACE_END