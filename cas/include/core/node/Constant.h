//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#ifndef CAS_CONSTANT_H
#define CAS_CONSTANT_H

#include "Expression.h"
#include "core/CAS.h"
#include <cmath>
#include <string>

CAS_NAMESPACE

namespace math {
    const double PI = M_PI;
    const double E = M_E;
    const double PHI = 1.6180339887498948482045868343656381;
}// namespace math

class Constant : public Expression {
public:
    explicit Constant(double value);

    explicit Constant() : Constant(0.0){};

    ~Constant() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool equals(Expression* expression) override;

    Constant* clone() override;

    Constant* derivative(char var) override;

    Constant* simplified() override;

    std::string latex() override;

    std::string stringify() override;

    std::string text() override;

    double getValue() const { return value; }

    static Constant* PI() { return new Constant{math::PI}; }

    static Constant* E() { return new Constant{math::E}; }

    static Constant* PHI() { return new Constant{math::PHI}; }

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

#endif//CAS_CONSTANT_H
