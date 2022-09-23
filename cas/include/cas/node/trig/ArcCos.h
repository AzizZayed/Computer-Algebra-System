//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ARCCOS_H
#define CAS_ARCCOS_H

#include "InverseTrigExpression.h"

CAS_NAMESPACE

class ArcCos : public InverseTrigExpression {
public:
    explicit ArcCos(Expression* argument);
    ArcCos() = delete;
    ~ArcCos() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    ArcCos* clone() override;
    Expression* _derivative(char variable) override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif//CAS_ARCCOS_H
