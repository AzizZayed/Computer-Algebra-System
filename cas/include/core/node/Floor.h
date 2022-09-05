//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ABS_H
#define CAS_ABS_H

#include "BracketFunction.h"
#include "core/CAS.h"

CAS_NAMESPACE

class Floor : public BracketFunction {
public:
    explicit Floor(Expression *argument);

    Floor() = delete;

    ~Floor() override = default;

    double evaluate(const std::unordered_map<char, double> &variables) override;

    Floor *clone() override;

    Expression *simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ABS_H
