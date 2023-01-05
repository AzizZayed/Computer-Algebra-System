//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SQRT_H
#define CAS_SQRT_H

#include "Root.h"

CAS_NAMESPACE

class Sqrt : public Root {
public:
    explicit Sqrt(ExprPtr base);
    Sqrt() = delete;
    ~Sqrt() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;

    static SqrtPtr from(ExprPtr base) { return std::make_shared<Sqrt>(base); }
};

CAS_NAMESPACE_END

#endif//CAS_SQRT_H
