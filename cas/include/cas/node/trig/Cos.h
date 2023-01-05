//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_COS_H
#define CAS_COS_H

#include "cas/CAS.h"
#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Cos : public TrigExpression {
public:
    explicit Cos(const ExprPtr& argument);
    Cos() = delete;
    ~Cos() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static CosPtr from(const ExprPtr& argument) { return std::make_shared<Cos>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_COS_H
