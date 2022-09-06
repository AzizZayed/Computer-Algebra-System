//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_CBRT_H
#define CAS_CBRT_H

#include "Root.h"

CAS_NAMESPACE

class Cbrt : public Root {
public:
    explicit Cbrt(Expression* base);
    Cbrt() = delete;
    ~Cbrt() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Cbrt* clone() override;
    Expression* derivative(char variable) override;
    Expression* simplified() override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string explicitText() override;
};

CAS_NAMESPACE_END

#endif//CAS_CBRT_H
