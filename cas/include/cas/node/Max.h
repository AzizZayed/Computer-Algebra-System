//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_MAX_H
#define CAS_MAX_H

#include "NaryExpression.h"

CAS_NAMESPACE

class Max : public NaryExpression {
public:
    explicit Max(std::vector<ExprPtr> expressions);

    Max() = delete;

    ~Max() override = default;

    double evaluate(const VariableMap& variables) override;

    ExprPtr clone() override;

    ExprPtr simplified() override;

    static MaxPtr from(const std::vector<ExprPtr>& expressions) { return std::make_shared<Max>(expressions); }
};

CAS_NAMESPACE_END

#endif//CAS_MAX_H
