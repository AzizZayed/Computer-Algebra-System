//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ROOT_H
#define CAS_ROOT_H

#include "Power.h"

CAS_NAMESPACE

class Root : public Power {
public:
    explicit Root(const ExpressionProperties& props, Expression* base, Expression* root);
    explicit Root(Expression* base, Expression* root);
    explicit Root(Expression* base, double root);

    Root() = delete;
    ~Root() override = default;

    double evaluate(const VariableMap& variables) override;
    Root* clone() override;
    Expression* simplified() override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;

    Expression* getRoot() const { return getExponent(); }
};

CAS_NAMESPACE_END

#endif//CAS_ROOT_H
