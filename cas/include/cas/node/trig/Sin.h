//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SIN_H
#define CAS_SIN_H

#include "cas/CAS.h"
#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Sin : public TrigExpression {
public:
    explicit Sin(Expression* argument);
    Sin() = delete;
    ~Sin() override = default;

    double evaluate(const VariableMap& variables) override;
    Sin* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_SIN_H
