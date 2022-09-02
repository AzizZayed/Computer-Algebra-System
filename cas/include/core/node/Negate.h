//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_NEGATE_H
#define CAS_NEGATE_H

#include "core/CAS.h"
#include "Expression.h"

CAS_NAMESPACE

class Negate : public Expression {
public:
    explicit Negate(Expression* parent, Expression* expression);
    explicit Negate(Expression* expression) : Negate(nullptr, expression) {}
    Negate() = delete;
    ~Negate() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(Expression* expression) override;

    Negate* clone(Expression* newParent) override;
    Negate* clone() override { return clone(nullptr); }

    Expression* derivative(Expression* newParent, char variable) override;
    Expression* simplified(Expression* newParent) override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string explicitText() override;
};

CAS_NAMESPACE_END

#endif //CAS_NEGATE_H
