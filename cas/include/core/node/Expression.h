//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_EXPRESSION_H
#define CAS_EXPRESSION_H

#include "core/CAS.h"
#include "IMathNode.h"
#include "ExpressionType.h"
#include <unordered_map>
#include <cstdlib>
#include <iostream>

CAS_NAMESPACE

class Expression : public IMathNode {
public:
    explicit Expression(Expression* parent, ExpressionType expressionType) : parent{parent}, expressionType{expressionType}
    {
        printf("cas::Expression(%hu)\n", expressionType);
    }

    virtual ~Expression() { printf("Destroy cas::Expression\n"); }

    Expression(const Expression& expression) = delete;

    virtual double evaluate(const std::unordered_map<char, double>& variables) = 0;
    virtual bool equals(Expression* expression) = 0;

    virtual Expression* clone(Expression* newParent) = 0;
    virtual Expression* clone() { return clone(nullptr); }

    virtual Expression* derivative(Expression* newParent, char variable) = 0;
    virtual Expression* simplified(Expression* newParent) = 0;

    ExpressionType getExpressionType() const { return expressionType; }
    Expression* getParent() const { return parent; }

protected:
    ExpressionType expressionType;
private:
    Expression* parent;

};

CAS_NAMESPACE_END

#endif //CAS_EXPRESSION_H
