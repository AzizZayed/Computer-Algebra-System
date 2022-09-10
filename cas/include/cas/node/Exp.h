//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#ifndef CAS_EXP_H
#define CAS_EXP_H

#include "Power.h"
#include "cas/CAS.h"

CAS_NAMESPACE

class Exp : public Power {
public:
    explicit Exp(Expression* exponent);

    Exp() = delete;

    ~Exp() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    Exp* clone() override;

    Expression* _derivative(char var) override;

    Expression* simplified() override;

    std::string explicitText() override;
};

CAS_NAMESPACE_END

#endif//CAS_EXP_H
