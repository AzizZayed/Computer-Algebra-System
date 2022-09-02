//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_EXPRESSION_H
#define CAS_EXPRESSION_H

#include "core/CAS.h"
#include "IMathNode.h"
#include "ExpressionType.h"
#include "ExpressionProperties.h"
#include <unordered_map>
#include <cstdlib>
#include <iostream>

CAS_NAMESPACE

class Expression : public IMathNode {
public:
    explicit Expression(Expression* parent, const ExpressionProperties& properties) : parent{parent}, properties{properties}
    {
#if DEBUG_CAS
        printf("cas::Expression(%hu)\n", properties.getType());
#endif
    }

    virtual ~Expression()
    {
#if DEBUG_CAS
        printf("Destroy cas::Expression\n");
#endif
    }

    Expression(const Expression& expression) = delete;

    virtual double evaluate(const std::unordered_map<char, double>& variables) = 0;
    virtual bool equals(Expression* expression) = 0;

    virtual Expression* clone(Expression* newParent) = 0;
    virtual Expression* clone() { return clone(nullptr); }

    virtual Expression* derivative(Expression* newParent, char variable) = 0;
    virtual Expression* simplified(Expression* newParent) = 0;

    ExpressionProperties getProperties() const { return properties; }
    Expression* getParent() const { return parent; }
    void setParent(Expression* newParent) { this->parent = newParent; }

    bool isNegated() const { return properties.getType() == ExpressionType::NEGATE; }

protected:
    ExpressionProperties properties;
    Expression* parent;
};

CAS_NAMESPACE_END

#endif //CAS_EXPRESSION_H
