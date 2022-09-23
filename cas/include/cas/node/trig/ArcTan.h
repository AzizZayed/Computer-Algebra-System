//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCTAN_H
#define CAS_ARCTAN_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcTan : public InverseTrigExpression {
public:
    explicit ArcTan(Expression* argument);
    ArcTan() = delete;
    ~ArcTan() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    ArcTan* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ARCTAN_H
