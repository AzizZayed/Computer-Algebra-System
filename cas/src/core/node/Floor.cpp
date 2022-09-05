//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/Floor.h"
#include "core/node/Constant.h"

CAS_NAMESPACE

Floor::Floor(Expression* argument)
: BracketFunction({ExpressionType::FLOOR, "floor_value", "floor"}, argument, "\u230A", "\u230B") {}

double Floor::evaluate(const std::unordered_map<char, double>& variables)
{
    return std::floor(argument->evaluate(variables));
}

Floor* Floor::clone()
{
    return new Floor(argument->clone());
}

Expression* Floor::simplified()
{
    if (argument->isOfType(ExpressionType::CONSTANT))
    {
        auto* constant = dynamic_cast<Constant*>(argument);
        return new Constant(std::floor(constant->getValue()));
    }
    return clone(); // TODO: simplify
}

CAS_NAMESPACE_END
