//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCSIN_H
#define CAS_ARCSIN_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcSin : public InverseTrigExpression {
public:
    explicit ArcSin(Expression* argument);
    ArcSin() = delete;
    ~ArcSin() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    ArcSin* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ARCSIN_H
