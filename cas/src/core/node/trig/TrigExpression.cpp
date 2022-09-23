//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/TrigExpression.h"
#include "cas/node/Log.h"
#include "cas/node/Operator.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

TrigExpression::TrigExpression(const ExpressionProperties& properties, Expression* argument)
    : UnaryExpression(properties, argument) {}

bool TrigExpression::_equals(Expression* other) {
    if (this == other)
        return true;

    if (other->getProperties().getType() != properties.getType())
        return false;

    auto* otherTrigFunction = dynamic_cast<TrigExpression*>(other);
    return argument->equals(otherTrigFunction->argument);
}

bool TrigExpression::needsParentheses() {
    return instanceof <Operator>(argument) || instanceof <Log>(argument) || argument->isOfType(ExpressionType::POWER) || argument->isOfType(ExpressionType::DIVIDE);
}

std::string TrigExpression::latex() {
    if (needsParentheses())
        return "\\" + properties.getShortName() + "{\\left(" + argument->latex() + "\\right)}";
    return "\\" + properties.getShortName() + "{" + argument->latex() + "}";
}

std::wstring TrigExpression::stringify() {
    if (needsParentheses())
        return toWstring(properties.getShortName()) + L" (" + argument->stringify() + L")";
    return toWstring(properties.getShortName()) + L" " + argument->stringify();
}

CAS_NAMESPACE_END