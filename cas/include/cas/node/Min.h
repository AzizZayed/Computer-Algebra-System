//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_MIN_H
#define CAS_MIN_H

#include "NaryExpression.h"

CAS_NAMESPACE

class Min : public NaryExpression {
public:
    explicit Min(std::vector<Expression*> expressions);

    Min() = delete;

    ~Min() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    Min* clone() override;

    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_MIN_H
