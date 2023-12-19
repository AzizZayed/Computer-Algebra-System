//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_UNARYFUNCTION_H
#define CAS_UNARYFUNCTION_H

#include "Expression.h"

CAS_NAMESPACE

class UnaryExpression : public Expression {
public:
    UnaryExpression() = delete;

    ~UnaryExpression() override;

    Expression* derivative(char var) override;

    Expression* getArgument() const { return argument; }

    std::string latex() override;

    std::string str() override;

    std::string text() override;

    std::string explicitText() override;

protected:
    explicit UnaryExpression(const ExpressionProperties& properties, Expression* argument);

protected:
    Expression* argument;
};

CAS_NAMESPACE_END

#endif//CAS_UNARYFUNCTION_H
