//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_CEIL_H
#define CAS_CEIL_H

#include "BracketExpression.h"

CAS_NAMESPACE

class Ceil : public BracketExpression {
public:
    explicit Ceil(const ExprPtr& argument);

    Ceil() = delete;

    ~Ceil() override = default;

    double evaluate(const VariableMap& variables) override;

    ExprPtr clone() override;

    ExprPtr simplified() override;

    static ExprPtr from(const ExprPtr& argument) {
        return std::make_shared<Ceil>(argument);
    }
};

CAS_NAMESPACE_END

#endif//CAS_CEIL_H
