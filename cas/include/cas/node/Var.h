//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_VARIABLE_H
#define CAS_VARIABLE_H

#include "Const.h"
#include "Expression.h"
#include "cas/CAS.h"
#include <string>

CAS_NAMESPACE

class Var : public Expression {
public:
    Var(char variable);
    explicit Var() : Var(VAR_X) {}

    ~Var() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool equals(Expression* expression) override;

    Var* clone() override;

    Const* derivative(char var) override;

    Var* simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    char getSymbol() const { return symbol; }

private:
    const char symbol;

public:
    static const char VAR_X = 'x';
};

CAS_NAMESPACE_END

#endif//CAS_VARIABLE_H
