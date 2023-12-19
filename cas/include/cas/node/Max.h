//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_MAX_H
#define CAS_MAX_H

#include "NaryExpression.h"

CAS_NAMESPACE

class Max : public NaryExpression {
public:
    explicit Max(const std::vector<Expression*>& expressions);

    Max() = delete;

    ~Max() override = default;

    double evaluate(const VariableMap& variables) override;

    Max* clone() override;

    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_MAX_H
