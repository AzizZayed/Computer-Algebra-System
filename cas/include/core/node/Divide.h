//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_DIVIDE_H
#define CAS_DIVIDE_H

#include "core/CAS.h"
#include "core/node/Expression.h"

CAS_NAMESPACE

class Divide : public Expression {
public:
    explicit Divide(Expression* parent, Expression* dividend, Expression* divisor);
    explicit Divide(Expression* dividend, Expression* divisor) : Divide(nullptr, dividend, divisor) {}
    Divide() = delete;
    ~Divide() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(Expression* expression) override;

    Divide* clone(Expression* newParent) override;
    Divide* clone() override { return clone(nullptr); }

    Divide* derivative(Expression* newParent, char variable) override;
    Expression* simplified(Expression* newParent) override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string explicitText() override;

private:
    Expression* dividend;
    Expression* divisor;
};

CAS_NAMESPACE_END

#endif //CAS_DIVIDE_H
