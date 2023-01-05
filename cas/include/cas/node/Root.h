//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_ROOT_H
#define CAS_ROOT_H

#include "Power.h"

CAS_NAMESPACE

class Root : public Power {
public:
    explicit Root(const ExpressionProperties& props, ExprPtr base, ExprPtr root);
    explicit Root(ExprPtr base, ExprPtr root);
    explicit Root(ExprPtr base, double root);

    Root() = delete;
    ~Root() override = default;

    double evaluate(const VariableMap& variables) override;
    ExprPtr clone() override;
    ExprPtr simplified() override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;

    ExprPtr getRoot() const { return getExponent(); }

    static RootPtr from(ExprPtr base, ExprPtr root) { return std::make_shared<Root>(base, root); }
    static RootPtr from(ExprPtr base, double root) { return std::make_shared<Root>(base, root); }
};

CAS_NAMESPACE_END

#endif//CAS_ROOT_H
