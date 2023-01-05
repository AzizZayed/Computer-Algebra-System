//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_MOD_H
#define CAS_MOD_H

#include "Expression.h"

CAS_NAMESPACE

class Mod : public Expr {
public:
    explicit Mod(ExprPtr dividend, ExprPtr divisor);
    Mod() = delete;
    ~Mod() override = default;

    double evaluate(const VariableMap& variables) override;
    bool _equals(ExprPtr expression) override;
    ExprPtr clone() override;
    ExprPtr simplified() override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;

    ExprPtr getDividend() const { return dividend; }
    ExprPtr getDivisor() const { return divisor; }

    static ModPtr from(ExprPtr dividend, ExprPtr divisor) { return std::make_shared<Mod>(dividend, divisor); }

private:
    ExprPtr dividend;
    ExprPtr divisor;
};

CAS_NAMESPACE_END

#endif//CAS_MOD_H
