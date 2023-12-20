//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_FLOOR_H
#define CAS_FLOOR_H

#include "BracketExpression.h"

CAS_NAMESPACE

class Floor : public BracketExpression {
public:
    explicit Floor(Expression* argument);

    Floor() = delete;

    ~Floor() override = default;

    double evaluate(const VariableMap& variables) override;

    Floor* clone() override;

    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif  //CAS_FLOOR_H
