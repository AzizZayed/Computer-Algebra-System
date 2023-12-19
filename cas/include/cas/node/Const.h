//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#ifndef CAS_CONSTANT_H
#define CAS_CONSTANT_H

#include "Expression.h"
#include <unordered_map>

CAS_NAMESPACE

class Const : public Expr {
public:
    explicit Const(double value);
    Const() = delete;
    ~Const() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(const ExprPtr& expression) override;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    double getValue() const { return value; }

    static ConstPtr PI() { return n(math::PI); }

    static ConstPtr E() { return n(math::E); }

    static ConstPtr PHI() { return n(math::PHI); }

    static ConstPtr zero() { return n(0.0); }

    static ConstPtr one() { return n(1.0); }

    static ConstPtr n(double value) { return std::make_shared<Const>(value); }
    static ConstPtr from(double value) { return n(value); }

    static bool floatingsEqual(double a, double b) {
        double max = std::max(1.0, std::max(std::fabs(a), std::fabs(b)));
        return std::fabs(a - b) <= std::numeric_limits<double>::epsilon() * max;
    }

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
