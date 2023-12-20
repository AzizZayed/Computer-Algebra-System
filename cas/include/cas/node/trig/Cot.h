//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_COT_H
#define CAS_COT_H

#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Cot : public TrigExpression {
public:
    explicit Cot(Expression* argument);
    Cot() = delete;
    ~Cot() override = default;

    double evaluate(const VariableMap& variables) override;
    Cot* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif  //CAS_COT_H
