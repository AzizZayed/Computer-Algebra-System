//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCCSC_H
#define CAS_ARCCSC_H

#include "InverseTrigFunction.h"

CAS_NAMESPACE

class ArcCsc : public InverseTrigFunction {
public:
    explicit ArcCsc(Expression* argument);
    ArcCsc() = delete;
    ~ArcCsc() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    ArcCsc* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ARCCSC_H
