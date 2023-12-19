//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_LOG_H
#define CAS_LOG_H

#include "Expression.h"

CAS_NAMESPACE

class Log : public Expression {
public:
    explicit Log(Expression* base, Expression* argument);

    explicit Log(double base, Expression* argument);

    explicit Log(Expression* argument);

    Log() = delete;

    ~Log() override;

    double evaluate(const VariableMap& variables) override;

    bool _equals(Expression* expression) override;

    Log* clone() override;

    Expression* _derivative(char var) override;

    Expression* simplified() override;

    std::string latex() override;

    std::string str() override;

    std::string text() override;

    std::string explicitText() override;

    Expression* getBase() const { return base; }

    Expression* getArgument() const { return argument; }

protected:
    explicit Log(const ExpressionProperties& props, Expression* base, Expression* argument);

    bool argumentNeedsParentheses();

protected:
    Expression* base;
    Expression* argument;
};

CAS_NAMESPACE_END

#endif//CAS_LOG_H
