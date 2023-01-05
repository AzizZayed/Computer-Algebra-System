//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#ifndef CAS_SUM_H
#define CAS_SUM_H

#include "Operator.h"

CAS_NAMESPACE

class Sum : public Operator {
public:
    explicit Sum(const std::vector<ExprPtr>& expressions);

    Sum() = delete;

    ~Sum() override = default;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    static SumPtr from(const std::vector<ExprPtr>& expressions) { return std::make_shared<Sum>(expressions); }

protected:
    double operate(double a, double b) override { return a + b; };

    bool needsParentheses(ExprPtr) override { return false; };
};

CAS_NAMESPACE_END

#endif//CAS_SUM_H
