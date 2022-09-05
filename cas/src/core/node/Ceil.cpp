//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/Ceil.h"
#include "core/node/Constant.h"

CAS_NAMESPACE

Ceil::Ceil(Expression* argument)
: BracketFunction({ExpressionType::CEIL, "ceiling", "ceil"}, argument, "\u2308", "\u2309") {}

double Ceil::evaluate(const std::unordered_map<char, double>& variables)
{
    return std::ceil(argument->evaluate(variables));
}

Ceil* Ceil::clone()
{
    return new Ceil(argument->clone());
}

Expression* Ceil::simplified()
{
    if (argument->isOfType(ExpressionType::CONSTANT))
    {
        auto* constant = dynamic_cast<Constant*>(argument);
        return new Constant(std::ceil(constant->getValue()));
    }
    return clone(); // TODO: simplify
}

CAS_NAMESPACE_END
