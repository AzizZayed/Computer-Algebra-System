//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#include "core/node/Constant.h"

CAS_NAMESPACE

const std::string Constant::PI_UNICODE = "\u03C0";
const std::string Constant::E_UNICODE = "e";
const std::string Constant::PHI_UNICODE = "\u03D5";

const std::string Constant::PI_LATEX = "\\pi";
const std::string Constant::E_LATEX = "e";
const std::string Constant::PHI_LATEX = "\\varphi";

Constant::Constant(double value)
: value{value}, Expression{{ExpressionType::CONSTANT, "constant", "const"}}
{
#if DEBUG_CAS
    std::string str = properties.getName();
    printf("%s(%f)\n", str.c_str(), value);
#endif
}

Constant::~Constant()
{
#if DEBUG_CAS
    printf("Destroy cas::Constant\n");
#endif
}

Constant* Constant::clone()
{
    return new Constant{value};
}

double Constant::evaluate(const std::unordered_map<char, double>& variables)
{
    return value;
}

bool Constant::equals(Expression* expression)
{
    if (this == expression)
        return true;

    if (expression->getProperties().getType() == ExpressionType::CONSTANT)
    {
        auto* constant = dynamic_cast<Constant*>(expression);
        return value == constant->getValue();
    }
    return false;
}

Constant* Constant::derivative(char var)
{
    return new Constant{0.0};
}

Constant* Constant::simplified()
{
    return clone();
}

std::string Constant::latex()
{
    if (value == math::PI)
    {
        return PI_LATEX;
    }
    if (value == math::E)
    {
        return E_LATEX;
    }
    if (value == math::PHI)
    {
        return PHI_LATEX;
    }

    return text();
}

std::string Constant::stringify()
{
    if (value == math::PI)
    {
        return PI_UNICODE;
    }
    if (value == math::E)
    {
        return E_UNICODE;
    }
    if (value == math::PHI)
    {
        return PHI_UNICODE;
    }

    return text();
}

std::string Constant::text()
{
    return std::to_string(value);
}

CAS_NAMESPACE_END
