//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_MOD_H
#define CAS_MOD_H

#include "Expression.h"

CAS_NAMESPACE

class Mod : public Expression {
public:
    explicit Mod(Expression* dividend, Expression* divisor);
    Mod() = delete;
    ~Mod() override;

    double evaluate(const VariableMap& variables) override;
    bool _equals(Expression* expression) override;
    Mod* clone() override;
    Expression* simplified() override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;

    Expression* getDividend() const { return dividend; }
    Expression* getDivisor() const { return divisor; }

private:
    Expression* dividend;
    Expression* divisor;
};

CAS_NAMESPACE_END

#endif//CAS_MOD_H
