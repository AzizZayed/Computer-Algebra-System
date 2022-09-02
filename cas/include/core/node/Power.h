//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_POWER_H
#define CAS_POWER_H

#include "core/CAS.h"
#include "core/node/Expression.h"

CAS_NAMESPACE

class Power : public Expression {
public:
    explicit Power(Expression* parent, Expression* base, Expression* exponent);
    explicit Power(Expression* base, Expression* exponent) : Power(nullptr, base, exponent) {}
    Power() = delete;
    ~Power() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(Expression* expression) override;

    Power* clone(Expression* newParent) override;
    Power* clone() override { return clone(nullptr); }

    Expression* derivative(Expression* newParent, char variable) override;
    Expression* simplified(Expression* newParent) override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string explicitText() override;
};

CAS_NAMESPACE_END

#endif //CAS_POWER_H
