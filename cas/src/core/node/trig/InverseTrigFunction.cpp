//
// Created by Abd-El-Aziz Zayed on 2022-09-09.
//

#include "cas/node/trig/InverseTrigFunction.h"

CAS_NAMESPACE

InverseTrigFunction::InverseTrigFunction(const ExpressionProperties& props, Expression* argument)
    : TrigFunction(props, argument) {}

//std::string InverseTrigFunction::latex() {
//    if (needsParentheses())
//        return "\\" + properties.getShortName() + "^{-1}{\\left(" + argument->latex() + "\\right)}";
//    return "\\" + properties.getShortName() + "^{-1}{" + argument->latex() + "}";
//}

CAS_NAMESPACE_END