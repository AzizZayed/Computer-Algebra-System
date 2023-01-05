//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_NEGATE_H
#define CAS_NEGATE_H

#include "UnaryExpression.h"

CAS_NAMESPACE

class Negate : public UnaryExpression {
public:
    explicit Negate(const ExprPtr& expression);

    Negate() = delete;

    ~Negate() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(const ExprPtr& expression) override;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

    static NegatePtr from(const ExprPtr& expression) { return std::make_shared<Negate>(expression); }

protected:
    bool needsParentheses();
};

CAS_NAMESPACE_END

#endif//CAS_NEGATE_H
