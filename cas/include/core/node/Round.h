//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ROUND_H
#define CAS_ROUND_H

#include "core/CAS.h"
#include "BracketFunction.h"

CAS_NAMESPACE

class Round : public BracketFunction {
public:
    explicit Round(Expression* argument);
    Round() = delete;
    ~Round() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Round* clone() override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif //CAS_ROUND_H
