//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//
#define _USE_MATH_DEFINES

#ifndef CAS_CONSTANT_H
#define CAS_CONSTANT_H

#ifdef WIN32
#include <corecrt_math_defines.h>
#endif

#include <cmath>
#include <string>
#include "core/CAS.h"
#include "Expression.h"

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

    std::wstring stringify() override;

    std::string text() override;

    double getValue() const { return value; }

    static Const* PI() { return new Const{math::PI}; }

    static Const* E() { return new Const{math::E}; }

    static Const* PHI() { return new Const{math::PHI}; }

private:
    double value;

public:
    static const wchar_t* PI_UNICODE;
    static const wchar_t* E_UNICODE;
    static const wchar_t* PHI_UNICODE;

    static const char* PI_LATEX;
    static const char* E_LATEX;
    static const char* PHI_LATEX;
};

CAS_NAMESPACE_END

#endif//CAS_CONSTANT_H
