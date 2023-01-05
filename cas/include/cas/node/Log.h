//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_LOG_H
#define CAS_LOG_H

#include "Expression.h"

CAS_NAMESPACE

class Log : public Expr {
public:
    explicit Log(ExprPtr base, ExprPtr argument);

    explicit Log(double base, ExprPtr argument);

    explicit Log(ExprPtr argument);

    Log() = delete;

    ~Log() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(ExprPtr expression) override;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

    ExprPtr getBase() const { return base; }

    ExprPtr getArgument() const { return argument; }

    static LogPtr from(ExprPtr base, ExprPtr argument) { return std::make_shared<Log>(base, argument); }
    static LogPtr from(double base, ExprPtr argument) { return std::make_shared<Log>(base, argument); }
    static LogPtr from(ExprPtr argument) { return std::make_shared<Log>(argument); }

protected:
    explicit Log(const ExpressionProperties& props, ExprPtr base, ExprPtr argument);

    bool argumentNeedsParentheses();

protected:
    ExprPtr base;
    ExprPtr argument;
};

CAS_NAMESPACE_END

#endif//CAS_LOG_H
