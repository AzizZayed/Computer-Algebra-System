//
// Created by Abd-El-Aziz Zayed on 2022-09-09.
//

#include "cas/node/trig/InverseTrigExpression.h"
#include "fmt/printf.h"

CAS_NAMESPACE

InverseTrigExpression::InverseTrigExpression(const ExpressionProperties& props, Expression* argument)
    : TrigExpression(props, argument) {}

std::string InverseTrigExpression::latex() {
    if (needsParentheses())
        return fmt::sprintf(R"(\text{%s}{\,\left(%s\right)})", properties.getName(), argument->latex());
    return fmt::sprintf("\\text{%s}{\\,%s}", properties.getName(), argument->latex());
}

CAS_NAMESPACE_END