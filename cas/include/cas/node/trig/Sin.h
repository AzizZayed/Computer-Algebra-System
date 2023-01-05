//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SIN_H
#define CAS_SIN_H

#include "cas/CAS.h"
#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Sin : public TrigExpression {
public:
    explicit Sin(const ExprPtr& argument);
    Sin() = delete;
    ~Sin() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static SinPtr from(const ExprPtr& argument) { return std::make_shared<Sin>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_SIN_H
