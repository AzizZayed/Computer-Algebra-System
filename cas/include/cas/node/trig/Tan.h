//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_TAN_H
#define CAS_TAN_H

#include "cas/CAS.h"
#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Tan : public TrigExpression {
public:
    explicit Tan(Expression* argument);
    Tan() = delete;
    ~Tan() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Tan* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_TAN_H
