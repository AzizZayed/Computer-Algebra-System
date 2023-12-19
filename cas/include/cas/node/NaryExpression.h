//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_NARYFUNCTION_H
#define CAS_NARYFUNCTION_H

#include "Expression.h"
#include <vector>

CAS_NAMESPACE

class NaryExpression : public Expr {
public:
    NaryExpression() = delete;

    ~NaryExpression() override = default;

    bool _equals(const ExprPtr& expression) override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

    std::vector<ExprPtr> getExpressions() const { return {expressions}; }

    template<typename F>
    bool all(F&& f) const;

    template<typename F>
    bool any(F&& f) const;

    template<typename F>
    void forEach(F&& f) const;

protected:
    explicit NaryExpression(const ExpressionProperties& props, std::vector<ExprPtr> expressions);

protected:
    std::vector<ExprPtr> expressions;
};

CAS_NAMESPACE_END

#endif//CAS_NARYFUNCTION_H
