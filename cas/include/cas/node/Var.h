//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_VARIABLE_H
#define CAS_VARIABLE_H

#include "Expression.h"

CAS_NAMESPACE

class Var : public Expr {
public:
    explicit Var(char variable);

    ~Var() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(const ExprPtr& expression) override;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    char getSymbol() const { return symbol; }

    static VarPtr var(char variable) { return Var::from(variable); }

    static VarPtr a() { return var('a'); }
    static VarPtr b() { return var('b'); }
    static VarPtr c() { return var('c'); }

    static VarPtr i() { return var('i'); }
    static VarPtr j() { return var('j'); }
    static VarPtr k() { return var('k'); }

    static VarPtr x() { return var('x'); }
    static VarPtr y() { return var('y'); }
    static VarPtr z() { return var('z'); }
    static VarPtr w() { return var('w'); }

    static VarPtr s() { return var('s'); }
    static VarPtr t() { return var('t'); }
    static VarPtr u() { return var('u'); }

    static VarPtr from(char variable) { return std::make_shared<Var>(variable); }

private:
    const char symbol;
};

CAS_NAMESPACE_END

#endif//CAS_VARIABLE_H
