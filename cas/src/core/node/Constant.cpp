//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#include "core/node/Constant.h"

CAS_NAMESPACE

const char* Constant::PI_UNICODE = "\u03C0";
const char* Constant::E_UNICODE = "e";
const char* Constant::PHI_UNICODE = "\u03D5";

const char* Constant::PI_LATEX = "\\pi";
const char* Constant::E_LATEX = "e";
const char* Constant::PHI_LATEX = "\\varphi";

Constant::Constant(Expression* parent, double value)
: value{value}, Expression{parent, ExpressionType::CONSTANT}
{
    std::string str = stringifyExpressionType(getExpressionType());
    printf("%s(%f)\n", str.c_str(), value);
}

Constant::~Constant()
{
    printf("Destroy cas::Constant\n");
}

Constant* Constant::clone(Expression* newParent)
{
    return new Constant{newParent, value};
}

double Constant::evaluate(const std::unordered_map<char, double>& variables)
{
    return value;
}

bool Constant::equals(Expression* expression)
{
    if (expression->getExpressionType() == ExpressionType::CONSTANT)
    {
        auto& constant = dynamic_cast<const Constant&>(*expression);
        return value == constant.getValue();
    }
    return false;
}

Constant* Constant::derivative(Expression* newParent, char variable)
{
    return new Constant{newParent, 0.0};
}

Constant* Constant::simplified(Expression* newParent)
{
    return clone(newParent);
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

std::string Constant::fullText()
{
    return stringifyExpressionType(expressionType) + "(" + text() + ")";
}

CAS_NAMESPACE_END
