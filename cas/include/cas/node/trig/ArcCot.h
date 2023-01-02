//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCCOT_H
#define CAS_ARCCOT_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcCot : public InverseTrigExpression {
public:
    explicit ArcCot(Expression* argument);
    ArcCot() = delete;
    ~ArcCot() override = default;

    double evaluate(const VariableMap& variables) override;
    ArcCot* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ARCCOT_H
