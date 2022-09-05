//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_EXPRESSION_H
#define CAS_EXPRESSION_H

#include "ExpressionProperties.h"
#include "ExpressionType.h"
#include "IMathNode.h"
#include "core/CAS.h"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

CAS_NAMESPACE

class Expression : public IMathNode {
public:
    explicit Expression(const ExpressionProperties &properties);

    virtual ~Expression();

    Expression(const Expression &expression) = delete;

    virtual double evaluate(const std::unordered_map<char, double> &variables);

    virtual bool equals(Expression *expression);

    virtual Expression *clone();

    virtual Expression *derivative(char var);

    virtual Expression *simplified();

    ExpressionProperties getProperties() const;

    Expression *getParent() const;

    void setParent(Expression *newParent);

    bool isNegated() const;

    bool isOfType(ExpressionType type) const;

    bool isOfSameType(Expression *expression) const;

    std::string explicitText() override;

protected:
    const ExpressionProperties properties;
    Expression *parent = nullptr;
};

CAS_NAMESPACE_END

#endif//CAS_EXPRESSION_H
