//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#ifndef CAS_CONSTANT_H
#define CAS_CONSTANT_H

#include "core/CAS.h"
#include "Expression.h"
#include <string>
#include <cmath>

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
    explicit Constant() : Constant(0.0) {};
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

public:
    static const std::string PI_UNICODE;
    static const std::string E_UNICODE;
    static const std::string PHI_UNICODE;

    static const std::string PI_LATEX;
    static const std::string E_LATEX;
    static const std::string PHI_LATEX;
};

CAS_NAMESPACE_END

#endif //CAS_CONSTANT_H
