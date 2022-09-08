//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/trig/TrigFunction.h"
#include "../../../util/StringUtils.h"
#include "core/node/Log.h"
#include "core/node/Operator.h"

CAS_NAMESPACE

TrigFunction::TrigFunction(const ExpressionProperties& properties, Expression* argument)
    : FixedInputFunction(properties, argument) {}

bool TrigFunction::equals(Expression* other) {
    if (this == other)
        return true;

    if (other->getProperties().getType() != properties.getType())
        return false;

    auto* otherTrigFunction = dynamic_cast<TrigFunction*>(other);
    return argument->equals(otherTrigFunction->argument);
}

bool TrigFunction::needsParentheses() {
    return instanceof <Operator>(argument) || instanceof <Log>(argument)
            || argument->isOfType(ExpressionType::POWER) || argument->isOfType(ExpressionType::DIVIDE);
}

std::string TrigFunction::latex() {
    if (needsParentheses())
        return "\\" + properties.getShortName() + "{\\left(" + argument->latex() + "\\right)}";
    return "\\" + properties.getShortName() + "{" + argument->latex() + "}";
}

std::wstring TrigFunction::stringify() {
    if (needsParentheses())
        return toWstring(properties.getShortName()) + L" (" + argument->stringify() + L")";
    return toWstring(properties.getShortName()) + L" " +  argument->stringify();
}

CAS_NAMESPACE_END