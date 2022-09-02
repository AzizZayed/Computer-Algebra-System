//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#ifndef CAS_PRODUCT_H
#define CAS_PRODUCT_H

#include "core/CAS.h"
#include "Operator.h"

CAS_NAMESPACE

class Product : public Operator {
public:
    explicit Product(Expression* parent, const std::vector<Expression*>& expressions);
    explicit Product(const std::vector<Expression*>& expressions) : Product(nullptr, expressions) {}
    Product() = delete;
    ~Product() override;

    Product* clone(Expression* newParent) override;
    Product* clone() override { return clone(nullptr); }

    Expression* derivative(Expression* newParent, char variable) override;
    Expression* simplified(Expression* newParent) override;

    std::string latex() override;
    std::string stringify() override;

protected:
    double operate(double a, double b) override;
    double neutral() override;
    bool needsParentheses(Expression* expression) override;
};

CAS_NAMESPACE_END

#endif //CAS_PRODUCT_H
