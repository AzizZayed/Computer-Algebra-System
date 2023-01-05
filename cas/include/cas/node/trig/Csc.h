//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_CSC_H
#define CAS_CSC_H

#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Csc : public TrigExpression {
public:
    explicit Csc(ExprPtr argument);
    Csc() = delete;
    ~Csc() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static CscPtr from(ExprPtr argument) { return std::make_shared<Csc>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_CSC_H
