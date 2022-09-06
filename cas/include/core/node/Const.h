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

class Const : public Expression {
public:
    Const(double value);

    explicit Const() : Const(0.0){};

    ~Const() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool equals(Expression* expression) override;

    Const* clone() override;

    Const* derivative(char var) override;

    Const* simplified() override;

    std::string latex() override;

    std::string stringify() override;

    std::string text() override;

    double getValue() const { return value; }

    static Const* PI() { return new Const{math::PI}; }

    static Const* E() { return new Const{math::E}; }

    static Const* PHI() { return new Const{math::PHI}; }

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
