//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SIGN_H
#define CAS_SIGN_H

#include "UnaryExpression.h"

CAS_NAMESPACE

class Sign : public UnaryExpression {
public:
    explicit Sign(const ExprPtr& argument);
    Sign() = delete;
    ~Sign() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(const ExprPtr& expression) override;

    ExprPtr clone() override;

    ExprPtr simplified() override;

    std::string latex() override;

    static SignPtr from(const ExprPtr& argument) { return std::make_shared<Sign>(argument); }

private:
    bool needsParentheses();
};

CAS_NAMESPACE_END

#endif//CAS_SIGN_H
