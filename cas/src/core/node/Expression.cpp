//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "core/node/Expression.h"

CAS_NAMESPACE

Expression::Expression(const ExpressionProperties& properties)
: properties{properties} {}

Expression::~Expression()
{
#if DEBUG_CAS
    printf("Destroy cas::Expression");
#endif
}

double Expression::evaluate(const std::unordered_map<char, double>& variables)
{
    throw std::runtime_error("Expression::evaluate() is not implemented for " + properties.getName());
}

bool Expression::equals(Expression* expression)
{
    throw std::runtime_error("Expression::equals() is not implemented for " + properties.getName());
}

Expression* Expression::clone()
{
    throw std::runtime_error("Expression::clone() is not implemented for " + properties.getName());
}

Expression* Expression::derivative(char var)
{
    throw std::runtime_error("Expression::derivative() is not implemented for " + properties.getName());
}

Expression* Expression::simplified()
{
    throw std::runtime_error("Expression::simplified() is not implemented for " + properties.getName());
}

ExpressionProperties Expression::getProperties() const { return properties; }
Expression* Expression::getParent() const { return parent; }
void Expression::setParent(Expression* newParent) { this->parent = newParent; }

bool Expression::isNegated() const { return properties.getType() == ExpressionType::NEGATE; }
bool Expression::isOfType(ExpressionType type) const { return properties.getType() == type; }
bool Expression::isOfSameType(Expression* expression) const
{
    return properties.getType() == expression->getProperties().getType();
}

std::string Expression::explicitText()
{
    return properties.getShortName() + "(" + text() + ")";
}

CAS_NAMESPACE_END
