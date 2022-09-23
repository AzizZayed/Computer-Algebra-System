//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_COS_H
#define CAS_COS_H

#include "cas/CAS.h"
#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Cos : public TrigExpression {
public:
    explicit Cos(Expression* argument);
    Cos() = delete;
    ~Cos() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Cos* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_COS_H
