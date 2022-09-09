//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_SINGLEINPUTFUNCTION_H
#define CAS_SINGLEINPUTFUNCTION_H

#include "Expression.h"
#include "cas/CAS.h"

CAS_NAMESPACE

class FixedInputFunction : public Expression {
public:
    FixedInputFunction() = delete;

    ~FixedInputFunction() override;

    Expression* getArgument() const { return argument; }

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

protected:
    explicit FixedInputFunction(const ExpressionProperties& properties, Expression* argument);

protected:
    Expression* argument;
};

CAS_NAMESPACE_END

#endif//CAS_SINGLEINPUTFUNCTION_H
