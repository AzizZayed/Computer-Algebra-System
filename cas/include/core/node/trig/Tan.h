//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_TAN_H
#define CAS_TAN_H

#include "core/CAS.h"
#include "core/node/trig/TrigFunction.h"

CAS_NAMESPACE

class Tan : public TrigFunction {
public:
    explicit Tan(Expression* argument);
    Tan() = delete;
    ~Tan() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Tan* clone() override;
    Expression* derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_TAN_H