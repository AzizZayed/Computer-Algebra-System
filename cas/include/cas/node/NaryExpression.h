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

    std::string str() override;

    std::string text() override;

    std::string explicitText() override;

    template <typename F>
    std::string toString(const std::string& name, const char* start, const char* delimiter, const char* end, F&& strExp);

    [[nodiscard]] std::vector<Expression*> getExpressions() const { return {expressions}; }

    template <typename F>
    bool all(F&& f) const;

    template <typename F>
    bool any(F&& f) const;

    template <typename F>
    void forEach(F&& f) const;

protected:
    explicit NaryExpression(const ExpressionProperties& props, const std::vector<Expression*>& expressions);

protected:
    std::vector<Expression*> expressions;
};

CAS_NAMESPACE_END

#endif  //CAS_NARYFUNCTION_H
