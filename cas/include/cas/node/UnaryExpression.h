//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_UNARYFUNCTION_H
#define CAS_UNARYFUNCTION_H

#include "Expression.h"

CAS_NAMESPACE

class UnaryExpression : public Expr {
public:
    UnaryExpression() = delete;

    ~UnaryExpression() override = default;

    ExprPtr derivative(char var) override;

    ExprPtr getArgument() const { return argument; }

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

protected:
    explicit UnaryExpression(const ExpressionProperties& properties, ExprPtr argument);

protected:
    ExprPtr argument;
};

CAS_NAMESPACE_END

#endif//CAS_UNARYFUNCTION_H
