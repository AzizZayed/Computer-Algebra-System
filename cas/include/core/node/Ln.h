//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_LN_H
#define CAS_LN_H

#include "core/CAS.h"
#include "Log.h"

CAS_NAMESPACE

class Ln : public Log {
public:
    explicit Ln(Expression* argument);
    Ln() = delete;
    ~Ln() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Ln* clone() override;
    Expression* derivative(char var) override;
    Expression* simplified() override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string explicitText() override;
};

CAS_NAMESPACE_END

#endif //CAS_LN_H
