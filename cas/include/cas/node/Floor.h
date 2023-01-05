//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_FLOOR_H
#define CAS_FLOOR_H

#include "BracketExpression.h"

CAS_NAMESPACE

class Floor : public BracketExpression {
public:
    explicit Floor(const ExprPtr& argument);

    Floor() = delete;

    ~Floor() override = default;

    double evaluate(const VariableMap& variables) override;

    ExprPtr clone() override;

    ExprPtr simplified() override;

    static FloorPtr from(const ExprPtr& argument) { return std::make_shared<Floor>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_FLOOR_H
