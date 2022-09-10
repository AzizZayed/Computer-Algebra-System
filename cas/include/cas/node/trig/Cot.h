//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_COT_H
#define CAS_COT_H

#include "cas/node/trig/TrigFunction.h"

CAS_NAMESPACE

class Cot : public TrigFunction {
public:
    explicit Cot(Expression* argument);
    Cot() = delete;
    ~Cot() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Cot* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_COT_H
