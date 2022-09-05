//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#include "core/CAS.h"
#include "core/node/Ln.h"
#include "core/node/Constant.h"
#include "core/node/Divide.h"

CAS_NAMESPACE

Ln::Ln(Expression* argument)
: Log({ExpressionType::NATURAL_LOGARITHM, "natural_logarithm", "ln"}, Constant::E(), argument) {}

double Ln::evaluate(const std::unordered_map<char, double>& variables)
{
    return log(argument->evaluate(variables));
}

Ln* Ln::clone()
{
    return new Ln(argument->clone());
}

Expression* Ln::derivative(char var)
{
    return new Divide(argument->derivative(var), argument->clone());
}

Expression* Ln::simplified()
{
    return new Ln(argument->simplified()); // TODO: Simplify
}

std::string Ln::latex()
{
    if (argumentNeedsParentheses())
        return "\\ln\\left(" + argument->latex() + "\\right)";
    return "\\ln" + argument->latex();
}

std::string Ln::stringify()
{
    if (argumentNeedsParentheses())
        return "ln(" + argument->stringify() + ")";
    return "ln" + argument->stringify();
}

std::string Ln::text()
{
    return "ln(" + argument->text() + ")";
}

std::string Ln::explicitText()
{
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END