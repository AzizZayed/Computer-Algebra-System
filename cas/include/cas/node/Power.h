//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_POWER_H
#define CAS_POWER_H

#include "cas/node/Expression.h"

CAS_NAMESPACE

class Power : public Expr {
public:
    explicit Power(const ExprPtr& base, const ExprPtr& exponent);

    explicit Power(const ExprPtr& base, double exponent);

    Power() = delete;

    ~Power() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(const ExprPtr& expression) override;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

    ExprPtr getBase() const { return base; }

    ExprPtr getExponent() const { return exponent; }

    static PowerPtr from(const ExprPtr& base, const ExprPtr& exponent) { return std::make_shared<Power>(base, exponent); }

protected:
    explicit Power(const ExpressionProperties& props, const ExprPtr& base, const ExprPtr& exponent);

    bool baseNeedsParentheses();

    bool exponentNeedsParentheses();

protected:
    ExprPtr base;
    ExprPtr exponent;
};

CAS_NAMESPACE_END

#endif//CAS_POWER_H
