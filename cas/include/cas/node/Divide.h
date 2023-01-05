//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_DIVIDE_H
#define CAS_DIVIDE_H

#include "cas/CAS.h"
#include "cas/node/Expression.h"

CAS_NAMESPACE

class Divide : public Expr {
public:
    Divide() = delete;
    explicit Divide(ExprPtr dividend, ExprPtr divisor);

    ~Divide() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(ExprPtr expression) override;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

    static DividePtr from(ExprPtr dividend, ExprPtr divisor) { return std::make_shared<Divide>(dividend, divisor); }

    ExprPtr getDividend() const { return dividend; }
    ExprPtr getDivisor() const { return divisor; }

private:
    void setParents();

private:
    ExprPtr dividend;
    ExprPtr divisor;
};

CAS_NAMESPACE_END

#endif//CAS_DIVIDE_H
