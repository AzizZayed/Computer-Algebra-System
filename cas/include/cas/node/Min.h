//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_MIN_H
#define CAS_MIN_H

#include "NaryExpression.h"

CAS_NAMESPACE

class Min : public NaryExpression {
public:
    explicit Min(std::vector<ExprPtr> expressions);

    Min() = delete;

    ~Min() override = default;

    double evaluate(const VariableMap& variables) override;

    ExprPtr clone() override;

    ExprPtr simplified() override;

    static MinPtr from(std::vector<ExprPtr> expressions) { return std::make_shared<Min>(expressions); }
};

CAS_NAMESPACE_END

#endif//CAS_MIN_H
