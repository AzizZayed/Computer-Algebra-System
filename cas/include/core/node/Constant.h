//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#ifndef CAS_CONSTANT_H
#define CAS_CONSTANT_H

#include "core/CAS.h"
#include "Expression.h"
#include <string>

CAS_NAMESPACE

namespace math {
    const double PI = M_PI;
    const double E = M_E;
    const double PHI = 1.6180339887498948482045868343656381;
}

class Constant : public Expression {
public:
    explicit Constant(Expression* parent, double value);
    explicit Constant(double value) : Constant(nullptr, value) {}
    Constant() = delete;
    ~Constant() override;

    double getValue() const { return value; }

    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(Expression* expression) override;

    Constant* clone(Expression* newParent) override;
    Constant* clone() override { return clone(nullptr); }

    Constant* derivative(Expression* newParent, char variable) override;
    Constant* simplified(Expression* newParent) override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string fullText() override;

    static Constant* PI(Expression* parent) { return new Constant{parent, math::PI}; }
    static Constant* E(Expression* parent) { return new Constant{parent, math::E}; }
    static Constant* PHI(Expression* parent) { return new Constant{parent, math::PHI}; }

    static Constant* PI() { return PI(nullptr); }
    static Constant* E() { return E(nullptr); }
    static Constant* PHI() { return PHI(nullptr); }

private:
    double value;
};

CAS_NAMESPACE_END

#endif //CAS_CONSTANT_H