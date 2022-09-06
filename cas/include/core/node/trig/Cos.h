//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_COS_H
#define CAS_COS_H

#include "core/CAS.h"
#include "core/node/trig/TrigFunction.h"

CAS_NAMESPACE

class Cos : public TrigFunction {
public:
    explicit Cos(Expression* argument);
    Cos() = delete;
    ~Cos() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Cos* clone() override;
    Expression* derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_COS_H
