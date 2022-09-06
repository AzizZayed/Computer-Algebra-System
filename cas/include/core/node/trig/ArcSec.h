//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCSEC_H
#define CAS_ARCSEC_H

#include "InverseTrigFunction.h"

CAS_NAMESPACE

class ArcSec : public InverseTrigFunction {
public:
    explicit ArcSec(Expression* argument);
    ArcSec() = delete;
    ~ArcSec() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    ArcSec* clone() override;
    Expression* derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ARCSEC_H
