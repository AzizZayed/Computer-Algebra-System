//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_LN_H
#define CAS_LN_H

#include "Log.h"
#include "cas/CAS.h"

CAS_NAMESPACE

class Ln : public Log {
public:
    explicit Ln(Expression* argument);

    Ln() = delete;

    ~Ln() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool _equals(Expression* expression) override;

    Ln* clone() override;

    Expression* _derivative(char var) override;

    Expression* simplified() override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;
};

CAS_NAMESPACE_END

#endif//CAS_LN_H
