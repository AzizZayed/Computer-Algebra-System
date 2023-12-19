//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_COT_H
#define CAS_COT_H

#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Cot : public TrigExpression {
public:
    explicit Cot(const ExprPtr& argument);
    Cot() = delete;
    ~Cot() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static CotPtr from(const ExprPtr& argument) { return std::make_shared<Cot>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_COT_H
