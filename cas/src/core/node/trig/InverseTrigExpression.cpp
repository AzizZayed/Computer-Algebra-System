//
// Created by Abd-El-Aziz Zayed on 2022-09-09.
//

#include "cas/node/trig/InverseTrigExpression.h"

CAS_NAMESPACE

InverseTrigExpression::InverseTrigExpression(const ExpressionProperties& props, Expression* argument)
    : TrigExpression(props, argument) {}

//std::string InverseTrigFunction::latex() {
//    if (needsParentheses())
//        return "\\" + properties.getShortName() + "^{-1}{\\left(" + argument->latex() + "\\right)}";
//    return "\\" + properties.getShortName() + "^{-1}{" + argument->latex() + "}";
//}

CAS_NAMESPACE_END