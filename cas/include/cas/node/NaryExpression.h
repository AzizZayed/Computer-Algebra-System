//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_NARYFUNCTION_H
#define CAS_NARYFUNCTION_H

#include "Expression.h"
#include "cas/CAS.h"
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

protected:
    explicit NaryExpression(const ExpressionProperties& props, std::vector<Expression*> expressions);

protected:
    std::vector<Expression*> expressions;
};

CAS_NAMESPACE_END

#endif//CAS_NARYFUNCTION_H
