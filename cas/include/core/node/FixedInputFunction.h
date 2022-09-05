//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_SINGLEINPUTFUNCTION_H
#define CAS_SINGLEINPUTFUNCTION_H

#include "core/CAS.h"
#include "Expression.h"

CAS_NAMESPACE

class FixedInputFunction : public Expression {
public:
    FixedInputFunction() = delete;
    ~FixedInputFunction() override {
        delete argument;
        argument = nullptr;
    };

    Expression* getArgument() const { return argument; }

    // TODO default implementation of string methods

protected:
    explicit FixedInputFunction(const ExpressionProperties& properties, Expression* argument)
    : Expression(properties), argument(argument)
    {
        this->argument->setParent(this);
    }

protected:
    Expression* argument;
};

CAS_NAMESPACE_END

#endif //CAS_SINGLEINPUTFUNCTION_H
