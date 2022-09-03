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
    explicit Expression(const ExpressionProperties &properties) : properties{properties} {}
    virtual ~Expression() = default;

    Expression(const Expression& expression) = delete;

    virtual double evaluate(const std::unordered_map<char, double>& variables) = 0;
    virtual bool equals(Expression* expression) = 0;
    virtual Expression* clone() = 0;
    virtual Expression* derivative(char var) = 0;
    virtual Expression* simplified() = 0;

    ExpressionProperties getProperties() const;
    Expression* getParent() const;
    void setParent(Expression* newParent);

    bool isNegated() const;
    bool isOfType(ExpressionType type) const;
    bool isOfSameType(Expression* expression) const;

    std::string explicitText() override;

protected:
    ExpressionProperties properties;
    Expression* parent = nullptr;
};

CAS_NAMESPACE_END

#endif //CAS_EXPRESSION_H
