//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCCOS_H
#define CAS_ARCCOS_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcCos : public InverseTrigExpression {
public:
    explicit ArcCos(const ExprPtr& argument);
    ArcCos() = delete;
    ~ArcCos() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static ArcCosPtr from(const ExprPtr& argument) { return std::make_shared<ArcCos>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_ARCCOS_H
