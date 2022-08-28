//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#ifndef CAS_CONSTANT_H
#define CAS_CONSTANT_H

#include "../CAS.h"
#include "ExpressionNode.h"

CAS_NAMESPACE

class Constant : public ExpressionNode {
public:
    explicit Constant(ExpressionNode* parent, double value);
    explicit Constant(double value) : Constant(nullptr, value) {}
    ~Constant() override;
    Constant() = delete;

    double getValue() const { return value; }

    Constant* clone(ExpressionNode* newParent) override;
    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(ExpressionNode* expression) override;
    ExpressionNode* derivative(ExpressionNode* newParent, char variable) override;
    ExpressionNode* simplified(ExpressionNode* newParent) override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;

private:
    double value;

public:
    constexpr static const double E = 2.718281828459045;
    constexpr static const double PI = 3.141592653589793;
    constexpr static const double PHI = 1.618033988749895;
};

CAS_NAMESPACE_END

#endif //CAS_CONSTANT_H
