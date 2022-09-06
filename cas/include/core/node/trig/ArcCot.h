//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCCOT_H
#define CAS_ARCCOT_H

#include "InverseTrigFunction.h"

CAS_NAMESPACE

class ArcCot : public InverseTrigFunction {
public:
    explicit ArcCot(Expression* argument);
    ArcCot() = delete;
    ~ArcCot() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    ArcCot* clone() override;
    Expression* derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ARCCOT_H