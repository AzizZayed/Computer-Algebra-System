//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ROUND_H
#define CAS_ROUND_H

#include "BracketExpression.h"

CAS_NAMESPACE

class Round : public BracketExpression {
public:
    explicit Round(ExprPtr argument);

    Round() = delete;

    ~Round() override = default;

    double evaluate(const VariableMap& variables) override;

    ExprPtr clone() override;

    ExprPtr simplified() override;

    static RoundPtr from(ExprPtr argument) { return std::make_shared<Round>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_ROUND_H
