//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_POWER_H
#define CAS_POWER_H

#include "Const.h"
#include "core/CAS.h"
#include "core/node/Expression.h"

CAS_NAMESPACE

class Power : public Expression {
public:
    explicit Power(Expression* base, Expression* exponent)
        : Power({ExpressionType::POWER, "power", "pow"}, base, exponent) {}

    explicit Power(Expression* base, double exponent)
        : Power({ExpressionType::POWER, "power", "pow"}, base, new Const(exponent)) {}

    Power() = delete;

    ~Power() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool equals(Expression* expression) override;

    Power* clone() override;

    Expression* derivative(char var) override;

    Expression* simplified() override;

    std::string latex() override;

    std::string stringify() override;

    std::string text() override;

    std::string explicitText() override;

    Expression* getBase() const { return base; }

    Expression* getExponent() const { return exponent; }

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
