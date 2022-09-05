//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_NEGATE_H
#define CAS_NEGATE_H

#include "core/CAS.h"
#include "Expression.h"
#include "FixedInputFunction.h"

CAS_NAMESPACE

class Negate : public FixedInputFunction {
public:
    explicit Negate(Expression* expression);
    Negate() = delete;
    ~Negate() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(Expression* expression) override;
    Negate* clone() override;
    Negate* derivative(char var) override;
    Expression* simplified() override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string explicitText() override;

protected:
    bool needsParentheses();
};

CAS_NAMESPACE_END

#endif //CAS_NEGATE_H
