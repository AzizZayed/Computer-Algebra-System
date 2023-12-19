//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCCOT_H
#define CAS_ARCCOT_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcCot : public InverseTrigExpression {
public:
    explicit ArcCot(const ExprPtr& argument);
    ArcCot() = delete;
    ~ArcCot() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static ArcCotPtr from(const ExprPtr& argument) { return std::make_shared<ArcCot>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_ARCCOT_H
