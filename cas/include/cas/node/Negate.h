//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_NEGATE_H
#define CAS_NEGATE_H

#include "Expression.h"
#include "UnaryExpression.h"
#include "cas/CAS.h"

CAS_NAMESPACE

class Negate : public UnaryExpression {
public:
    explicit Negate(Expression* expression);

    Negate() = delete;

    ~Negate() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool _equals(Expression* expression) override;

    Negate* clone() override;

    Negate* _derivative(char var) override;

    Expression* simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

protected:
    bool needsParentheses();
};

CAS_NAMESPACE_END

#endif//CAS_NEGATE_H
