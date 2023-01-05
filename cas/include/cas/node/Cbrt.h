//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_CBRT_H
#define CAS_CBRT_H

#include "Root.h"

CAS_NAMESPACE

class Cbrt : public Root {
public:
    explicit Cbrt(ExprPtr base);
    Cbrt() = delete;
    ~Cbrt() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr _derivative(char variable) override;
    ExprPtr simplified() override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;

    static CbrtPtr from(ExprPtr base) { return std::make_shared<Cbrt>(base); }
};

CAS_NAMESPACE_END

#endif//CAS_CBRT_H
