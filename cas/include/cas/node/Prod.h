//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#ifndef CAS_PRODUCT_H
#define CAS_PRODUCT_H

#include "Operator.h"

CAS_NAMESPACE

class Prod : public Operator {
public:
    explicit Prod(const std::vector<ExprPtr>& expressions);

    Prod() = delete;

    ~Prod() override = default;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    static ProdPtr from(const std::vector<ExprPtr>& expressions) { return std::make_shared<Prod>(expressions); }

protected:
    double operate(double a, double b) override { return a * b; };

    bool needsParentheses(ExprPtr expression) override;
};

CAS_NAMESPACE_END

#endif//CAS_PRODUCT_H
