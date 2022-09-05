//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#ifndef CAS_SUM_H
#define CAS_SUM_H

#include "Operator.h"
#include "core/CAS.h"

CAS_NAMESPACE

class Sum : public Operator {
public:
    explicit Sum(const std::vector<Expression*>& expressions);

    Sum() = delete;

    ~Sum() override;

    Sum* clone() override;

    Sum* derivative(char var) override;

    Expression* simplified() override;

    std::string latex() override;

    std::string stringify() override;

protected:
    double operate(double a, double b) override { return a + b; };

    bool needsParentheses(Expression* expression) override { return false; };
};

CAS_NAMESPACE_END

#endif//CAS_SUM_H
