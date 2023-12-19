//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_OPERATOR_H
#define CAS_OPERATOR_H

#include "Expression.h"
#include <vector>

CAS_NAMESPACE

class Operator : public Expr {
public:
    explicit Operator(const ExpressionProperties& props, double neutral, char symbol, std::vector<ExprPtr> expressions);

    Operator() = delete;

    ~Operator() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(const ExprPtr& expression) override;

    std::string text() override;

    std::string explicitText() override;

    char getSymbol() const { return symbol; }

    std::vector<ExprPtr> getExpressions() const { return {expressions}; }
    size_t getExpressionsSize() const { return expressions.size(); }

protected:
    virtual double operate(double a, double b) = 0;

    virtual bool needsParentheses(const ExprPtr& expression) = 0;

protected:
    const double neutral;
    const char symbol;
    std::vector<ExprPtr> expressions;
};

CAS_NAMESPACE_END

#endif//CAS_OPERATOR_H
