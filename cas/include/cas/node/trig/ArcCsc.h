//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCCSC_H
#define CAS_ARCCSC_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcCsc : public InverseTrigExpression {
public:
    explicit ArcCsc(ExprPtr argument);
    ArcCsc() = delete;
    ~ArcCsc() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static ArcCscPtr from(ExprPtr argument) { return std::make_shared<ArcCsc>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_ARCCSC_H
