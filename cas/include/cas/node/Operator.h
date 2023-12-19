//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_OPERATOR_H
#define CAS_OPERATOR_H

#include <vector>
#include "Expression.h"

CAS_NAMESPACE

class Operator : public Expression {
public:
    explicit Operator(const ExpressionProperties& props, double neutral, char symbol, std::vector<Expression*> expressions);

    Operator() = delete;

    ~Operator() override;

    double evaluate(const VariableMap& variables) override;

    bool _equals(Expression* expression) override;

    std::string text() override;

    std::string explicitText() override;

    [[nodiscard]] char getSymbol() const { return symbol; }

    [[nodiscard]] std::vector<Expression*> getExpressions() const { return {expressions}; }
    [[nodiscard]] size_t getExpressionsSize() const { return expressions.size(); }

protected:
    virtual double operate(double a, double b) = 0;

    virtual bool needsParentheses(Expression* expression) = 0;

protected:
    const double neutral;
    const char symbol;
    std::vector<Expression*> expressions;
};

CAS_NAMESPACE_END

#endif//CAS_OPERATOR_H
