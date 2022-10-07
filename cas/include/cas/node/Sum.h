//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#ifndef CAS_SUM_H
#define CAS_SUM_H

#include "Operator.h"

CAS_NAMESPACE

class Sum : public Operator {
public:
    explicit Sum(const std::vector<Expression*>& expressions);

    Sum() = delete;

    ~Sum() override = default;

    Sum* clone() override;

    Sum* _derivative(char var) override;

    Expression* simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

protected:
    double operate(double a, double b) override { return a + b; };

    bool needsParentheses(Expression*) override { return false; };
};

CAS_NAMESPACE_END

#endif//CAS_SUM_H
