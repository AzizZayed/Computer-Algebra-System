//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_POWER_H
#define CAS_POWER_H

#include "cas/node/Expression.h"

CAS_NAMESPACE

class Power : public Expression {
public:
    explicit Power(Expression* base, Expression* exponent);

    explicit Power(Expression* base, double exponent);

    Power() = delete;

    ~Power() override;

    double evaluate(const VariableMap& variables) override;

    bool _equals(Expression* expression) override;

    Power* clone() override;

    Expression* _derivative(char var) override;

    Expression* simplified() override;

    std::string latex() override;

    std::string str() override;

    std::string text() override;

    std::string explicitText() override;

    [[nodiscard]] Expression* getBase() const { return base; }

    [[nodiscard]] Expression* getExponent() const { return exponent; }

protected:
    explicit Power(const ExpressionProperties& props, Expression* base, Expression* exponent);

    bool baseNeedsParentheses();

    bool exponentNeedsParentheses();

protected:
    Expression* base;
    Expression* exponent;
};

CAS_NAMESPACE_END

#endif//CAS_POWER_H
