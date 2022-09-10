//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_UNARYFUNCTION_H
#define CAS_UNARYFUNCTION_H

#include "Expression.h"
#include "cas/CAS.h"

CAS_NAMESPACE

class UnaryFunction : public Expression {
public:
    UnaryFunction() = delete;

    ~UnaryFunction() override;

    Expression* derivative(char var) override;

    Expression* getArgument() const { return argument; }

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

protected:
    explicit UnaryFunction(const ExpressionProperties& properties, Expression* argument);

protected:
    Expression* argument;
};

CAS_NAMESPACE_END

#endif//CAS_UNARYFUNCTION_H
