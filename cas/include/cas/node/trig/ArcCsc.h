//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCCSC_H
#define CAS_ARCCSC_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcCsc : public InverseTrigExpression {
public:
    explicit ArcCsc(Expression* argument);
    ArcCsc() = delete;
    ~ArcCsc() override = default;

    double evaluate(const VariableMap& variables) override;
    ArcCsc* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ARCCSC_H
