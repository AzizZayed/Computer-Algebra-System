//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCTAN_H
#define CAS_ARCTAN_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcTan : public InverseTrigExpression {
public:
    explicit ArcTan(ExprPtr argument);
    ArcTan() = delete;
    ~ArcTan() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static ArcTanPtr from(ExprPtr argument) { return std::make_shared<ArcTan>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_ARCTAN_H
