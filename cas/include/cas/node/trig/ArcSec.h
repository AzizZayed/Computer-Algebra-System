//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCSEC_H
#define CAS_ARCSEC_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcSec : public InverseTrigExpression {
public:
    explicit ArcSec(const ExprPtr& argument);
    ArcSec() = delete;
    ~ArcSec() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    static ArcSecPtr from(const ExprPtr& argument) { return std::make_shared<ArcSec>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_ARCSEC_H
