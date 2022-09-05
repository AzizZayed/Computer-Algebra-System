//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#ifndef CAS_PRODUCT_H
#define CAS_PRODUCT_H

#include "Operator.h"
#include "core/CAS.h"

CAS_NAMESPACE

class Product : public Operator {
public:
    explicit Product(const std::vector<Expression *> &expressions);

    Product() = delete;

    ~Product() override;

    Product *clone() override;

    Expression *derivative(char var) override;

    Expression *simplified() override;

    std::string latex() override;

    std::string stringify() override;

protected:
    double operate(double a, double b) override { return a * b; };

    bool needsParentheses(Expression *expression) override;
};

CAS_NAMESPACE_END

#endif//CAS_PRODUCT_H
