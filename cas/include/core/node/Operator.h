//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_OPERATOR_H
#define CAS_OPERATOR_H

#include "core/CAS.h"
#include "Expression.h"
#include <utility>
#include <vector>

CAS_NAMESPACE

class Operator : public Expression {
public:
    explicit Operator(Expression* parent, const ExpressionProperties& props, char symbol, const std::vector<Expression*>& expressions);
    explicit Operator(const ExpressionProperties& props, char symbol, const std::vector<Expression*>& expressions)
        : Operator(nullptr, props, symbol, expressions) {}
    Operator() = delete;
    ~Operator() override;

    char getSymbol() const { return symbol; }
    std::vector<Expression*> getExpressions() const { return {expressions}; }

    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(Expression* expression) override;

    std::string text() override;
    std::string explicitText() override;

protected:
    virtual double operate(double a, double b) = 0;
    virtual double neutral() = 0;
    virtual bool needsParentheses(Expression* expression) = 0;

protected:
    char symbol;
    std::vector<Expression*> expressions;
};

CAS_NAMESPACE_END

#endif //CAS_OPERATOR_H
