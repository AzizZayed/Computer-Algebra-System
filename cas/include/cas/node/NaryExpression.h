//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_NARYFUNCTION_H
#define CAS_NARYFUNCTION_H

#include "Expression.h"
#include <vector>

CAS_NAMESPACE

class NaryExpression : public Expression {
public:
    NaryExpression() = delete;

    ~NaryExpression() override;

    bool _equals(Expression* expression) override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

    std::vector<Expression*> getExpressions() const { return {expressions}; }

    template<typename F>
    bool all(F&& f) const {
        return std::all_of(expressions.begin(), expressions.end(), f);
    }

    template<typename F>
    bool any(F&& f) const {
        return std::any_of(expressions.begin(), expressions.end(), f);
    }

    template<typename F>
    void forEach(F&& f) const {
        std::for_each(expressions.begin(), expressions.end(), f);
    }

protected:
    explicit NaryExpression(const ExpressionProperties& props, std::vector<Expression*> expressions);

protected:
    std::vector<Expression*> expressions;
};

CAS_NAMESPACE_END

#endif//CAS_NARYFUNCTION_H
