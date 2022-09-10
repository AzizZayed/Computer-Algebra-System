//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SIGN_H
#define CAS_SIGN_H

#include "UnaryFunction.h"
#include "cas/CAS.h"

CAS_NAMESPACE

class Sign : public UnaryFunction {
public:
    explicit Sign(Expression* argument);
    Sign() = delete;
    ~Sign() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool _equals(Expression* expression) override;

    Sign* clone() override;

    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_SIGN_H
