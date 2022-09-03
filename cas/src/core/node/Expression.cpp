//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "core/node/Expression.h"

CAS_NAMESPACE

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
