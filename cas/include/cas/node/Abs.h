//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ABS_H
#define CAS_ABS_H

#include "BracketExpression.h"

CAS_NAMESPACE

class Abs : public BracketExpression {
public:
    explicit Abs(Expression* argument);

    Abs() = delete;

    ~Abs() override = default;

    double evaluate(const VariableMap& variables) override;

    Abs* clone() override;

    Expression* simplified() override;

    std::string text() override;
};

CAS_NAMESPACE_END

#endif//CAS_ABS_H
