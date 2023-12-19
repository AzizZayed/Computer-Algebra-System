//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SEC_H
#define CAS_SEC_H

#include "cas/CAS.h"
#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Sec : public TrigExpression {
public:
    explicit Sec(const ExprPtr& argument);
    Sec() = delete;
    ~Sec() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static SecPtr from(const ExprPtr& argument) { return std::make_shared<Sec>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_SEC_H
