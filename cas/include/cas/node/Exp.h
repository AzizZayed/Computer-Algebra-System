//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#ifndef CAS_EXP_H
#define CAS_EXP_H

#include "Power.h"

CAS_NAMESPACE

class Exp : public Power {
public:
    explicit Exp(const ExprPtr& exponent);

    Exp() = delete;

    ~Exp() override = default;

    double evaluate(const VariableMap& variables) override;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string explicitText() override;

    static ExpPtr from(const ExprPtr& exponent) { return std::make_shared<Exp>(exponent); }
};

CAS_NAMESPACE_END

#endif//CAS_EXP_H
