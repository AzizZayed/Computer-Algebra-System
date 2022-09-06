//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SIN_H
#define CAS_SIN_H

#include "core/CAS.h"
#include "core/node/trig/TrigFunction.h"

CAS_NAMESPACE

class Sin : public TrigFunction {
public:
    explicit Sin(Expression* argument);
    Sin() = delete;
    ~Sin() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Sin* clone() override;
    Expression* derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_SIN_H
