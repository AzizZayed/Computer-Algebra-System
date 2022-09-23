//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SEC_H
#define CAS_SEC_H

#include "cas/CAS.h"
#include "cas/node/trig/TrigExpression.h"

CAS_NAMESPACE

class Sec : public TrigExpression {
public:
    explicit Sec(Expression* argument);
    Sec() = delete;
    ~Sec() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Sec* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_SEC_H
