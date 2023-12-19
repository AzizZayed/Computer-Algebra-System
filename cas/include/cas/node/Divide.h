//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_DIVIDE_H
#define CAS_DIVIDE_H

#include "cas/CAS.h"
#include "cas/node/Expression.h"

CAS_NAMESPACE

class Divide : public Expression {
public:
    explicit Divide(Expression* dividend, Expression* divisor);

    Divide() = delete;

    ~Divide() override;

    double evaluate(const VariableMap& variables) override;

    bool _equals(Expression* expression) override;

    Divide* clone() override;

    Divide* _derivative(char var) override;

    Expression* simplified() override;

    std::string latex() override;

    std::string str() override;

    std::string text() override;

    std::string explicitText() override;

    [[nodiscard]] Expression* getDividend() const { return dividend; }
    [[nodiscard]] Expression* getDivisor() const { return divisor; }

private:
    Expression* dividend;
    Expression* divisor;
};

CAS_NAMESPACE_END

#endif//CAS_DIVIDE_H
