//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_TAN_H
#define CAS_TAN_H

#include "cas/CAS.h"
#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Tan : public TrigExpression {
public:
    explicit Tan(const ExprPtr& argument);
    Tan() = delete;
    ~Tan() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static TanPtr from(const ExprPtr& argument) { return std::make_shared<Tan>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_TAN_H
