//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_LN_H
#define CAS_LN_H

#include "Log.h"

CAS_NAMESPACE

class Ln : public Log {
public:
    explicit Ln(ExprPtr argument);

    Ln() = delete;

    ~Ln() override = default;

    double evaluate(const VariableMap& variables) override;

    bool _equals(ExprPtr expression) override;

    ExprPtr clone() override;

    ExprPtr _derivative(char var) override;

    ExprPtr simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

    static LnPtr from(ExprPtr argument) { return std::make_shared<Ln>(argument); }
};

CAS_NAMESPACE_END

#endif//CAS_LN_H
