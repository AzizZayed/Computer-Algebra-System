//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_SQRT_H
#define CAS_SQRT_H

#include "Root.h"

CAS_NAMESPACE

class Sqrt : public Root {
public:
    explicit Sqrt(Expression* base);
    Sqrt() = delete;
    ~Sqrt() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Sqrt* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;
};

CAS_NAMESPACE_END

#endif//CAS_SQRT_H
