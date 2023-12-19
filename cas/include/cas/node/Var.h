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
    explicit Var() : Var('x') {}

    ~Var() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(Expression* expression) override;

    Var* clone() override;

    Expression* _derivative(char var) override;

    Var* simplified() override;

    std::string latex() override;

    std::string str() override;

    std::string text() override;

    char getSymbol() const { return symbol; }

    static Var* var(char variable) { return new Var(variable); }

    static Var* a() { return var('a'); }
    static Var* b() { return var('b'); }
    static Var* c() { return var('c'); }

    static Var* i() { return var('i'); }
    static Var* j() { return var('j'); }
    static Var* k() { return var('k'); }

    static Var* x() { return var('x'); }
    static Var* y() { return var('y'); }
    static Var* z() { return var('z'); }
    static Var* w() { return var('w'); }

    static Var* s() { return var('s'); }
    static Var* t() { return var('t'); }
    static Var* u() { return var('u'); }

private:
    const char symbol;
};

CAS_NAMESPACE_END

#endif//CAS_VARIABLE_H
