//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#include "core/node/Constant.h"

CAS_NAMESPACE

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
    return new Constant{newParent, this->value};
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
    return std::to_string(value);
}

std::string Constant::stringify()
{
    return std::to_string(value);
}

std::string Constant::text()
{
    return std::to_string(value);
}

std::string Constant::fullText()
{
    return stringifyExpressionType(expressionType) + "(" + std::to_string(value) + ")";
}

CAS_NAMESPACE_END
