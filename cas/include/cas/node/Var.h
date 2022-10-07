//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_VARIABLE_H
#define CAS_VARIABLE_H

#include "Expression.h"

CAS_NAMESPACE

class Var : public Expression {
public:
    explicit Var(char variable);
    explicit Var() : Var(VAR_X) {}

    ~Var() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool _equals(Expression* expression) override;

    Var* clone() override;

    Expression* _derivative(char var) override;

    Var* simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    char getSymbol() const { return symbol; }

    static Var* var(char variable) { return new Var(variable); }

    static Var* a() { return new Var(VAR_A); }
    static Var* b() { return new Var(VAR_B); }

    static Var* x() { return new Var(VAR_X); }
    static Var* y() { return new Var(VAR_Y); }
    static Var* z() { return new Var(VAR_Z); }
    static Var* w() { return new Var(VAR_W); }

    static Var* t() { return new Var(VAR_T); }
    static Var* s() { return new Var(VAR_S); }

private:
    const char symbol;

public:
    static const char VAR_A = 'a';
    static const char VAR_B = 'b';

    static const char VAR_X = 'x';
    static const char VAR_Y = 'y';
    static const char VAR_Z = 'z';
    static const char VAR_W = 'w';

    static const char VAR_T = 't';
    static const char VAR_S = 's';
};

CAS_NAMESPACE_END

#endif//CAS_VARIABLE_H
