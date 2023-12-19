//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//
#ifndef CAS_CONSTANT_H
#define CAS_CONSTANT_H

#include "Expression.h"
#include <unordered_map>

CAS_NAMESPACE

class Const : public Expression {
public:
    explicit Const(double value);

    explicit Const() : Const(0.0) {};

    ~Const() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(Expression* expression) override;

    bool is(double val, double eps) const;

    bool isSymbol() const;

    Const* clone() override;

    Const* _derivative(char var) override;

    Const* simplified() override;

    std::string latex() override;

    std::string str() override;

    std::string text() override;

    double getValue() const { return value; }

    static Const* PI() { return new Const{math_constants::PI}; }

    static Const* E() { return new Const{math_constants::E}; }

    static Const* PHI() { return new Const{math_constants::PHI}; }

    static Const* zero() { return new Const; }

    static Const* one() { return new Const{1.0}; }

    static Const* n(double value) { return new Const{value}; }

private:
    double value;

public:
    static const char* PI_UNICODE;
    static const char* E_UNICODE;
    static const char* PHI_UNICODE;

    static const char* PI_LATEX;
    static const char* E_LATEX;
    static const char* PHI_LATEX;
};

CAS_NAMESPACE_END

#endif//CAS_CONSTANT_H
