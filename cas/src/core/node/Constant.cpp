//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#include "Constant.h"

CAS_NAMESPACE

Constant::Constant(ExpressionNode* parent, double value)
: value{value}, ExpressionNode{parent, ExpressionType::CONSTANT}
{
    printf("cas::Constant(%f)\n", value);
}

Constant::~Constant()
{
    printf("Destroy cas::Constant\n");
}

Constant* Constant::clone(ExpressionNode* newParent)
{
    return new Constant{newParent, this->value};
}

double Constant::evaluate(const std::unordered_map<char, double>& variables)
{
    return value;
}

bool Constant::equals(ExpressionNode* expression)
{
    if (expression->getExpressionType() == ExpressionType::CONSTANT)
    {
        auto& constant = dynamic_cast<const Constant&>(*expression);
        return value == constant.getValue();
    }
    return false;
}

ExpressionNode* Constant::derivative(ExpressionNode* newParent, char variable)
{
    return new Constant{newParent, 0.0};
}

ExpressionNode* Constant::simplified(ExpressionNode* newParent)
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

CAS_NAMESPACE_END
