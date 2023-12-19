//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCSIN_H
#define CAS_ARCSIN_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcSin : public InverseTrigExpression {
public:
    explicit ArcSin(const ExprPtr& argument);
    ArcSin() = delete;
    ~ArcSin() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static ArcSinPtr from(const ExprPtr& argument) { return std::make_shared<ArcSin>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_ARCSIN_H
