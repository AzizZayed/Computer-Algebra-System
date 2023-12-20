//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCSEC_H
#define CAS_ARCSEC_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcSec : public InverseTrigExpression {
public:
    explicit ArcSec(Expression* argument);
    ArcSec() = delete;
    ~ArcSec() override = default;

    double evaluate(const VariableMap& variables) override;
    ArcSec* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif  //CAS_ARCSEC_H
