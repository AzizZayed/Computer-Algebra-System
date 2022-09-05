//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_CEIL_H
#define CAS_CEIL_H

#include "BracketFunction.h"
#include "core/CAS.h"

CAS_NAMESPACE

class Ceil : public BracketFunction {
public:
    explicit Ceil(Expression *argument);

    Ceil() = delete;

    ~Ceil() override = default;

    double evaluate(const std::unordered_map<char, double> &variables) override;

    Ceil *clone() override;

    Expression *simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_CEIL_H
