//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#ifndef CAS_SUM_H
#define CAS_SUM_H

#include "core/CAS.h"
#include "Operator.h"

CAS_NAMESPACE

class Sum : public Operator {
public:
    explicit Sum(Expression* parent, const std::vector<Expression*>& expressions);
    explicit Sum(const std::vector<Expression*>& expressions) : Sum(nullptr, expressions) {}
    Sum() = delete;
    ~Sum() override;

    Sum* clone(Expression* newParent) override;
    Sum* clone() override { return clone(nullptr); }

    Sum* derivative(Expression* newParent, char variable) override;
    Expression* simplified(Expression* newParent) override;

    std::string latex() override;
    std::string stringify() override;

protected:
    double operate(double a, double b) override;
    double neutral() override;
    bool needsParentheses(Expression* expression) override;
};

CAS_NAMESPACE_END

#endif //CAS_SUM_H
