//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_EXPRESSION_H
#define CAS_EXPRESSION_H

#include <unordered_map>
#include <cstdlib>

#include "../CAS.h"
#include "IMathNode.h"

CAS_NAMESPACE

enum ExpressionType : size_t {
    CONSTANT = 0,
};

class ExpressionNode : public IMathNode {
public:
    explicit ExpressionNode(ExpressionNode* parent, ExpressionType expressionType) : parent{parent}, expressionType{expressionType}
    {
        printf("cas::ExpressionNode(%zu)\n", expressionType);
    }

    virtual ~ExpressionNode() { printf("Destroy cas::ExpressionNode\n"); }

    ExpressionNode(const ExpressionNode& expression) = delete;

    virtual ExpressionNode* clone(ExpressionNode* newParent) = 0;
    virtual double evaluate(const std::unordered_map<char, double>& variables) = 0;
    virtual bool equals(ExpressionNode* expression) = 0;
    virtual ExpressionNode* derivative(ExpressionNode* newParent, char variable) = 0;
    virtual ExpressionNode* simplified(ExpressionNode* newParent) = 0;

    ExpressionType getExpressionType() const { return expressionType; }
    ExpressionNode* getParent() const { return parent; }

private:
    ExpressionType expressionType;
    ExpressionNode* parent;
};

CAS_NAMESPACE_END

#endif //CAS_EXPRESSION_H
