//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_CSC_H
#define CAS_CSC_H

#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Csc : public TrigExpression {
public:
    explicit Csc(Expression* argument);
    Csc() = delete;
    ~Csc() override = default;

    double evaluate(const VariableMap& variables) override;
    Csc* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif  //CAS_CSC_H
