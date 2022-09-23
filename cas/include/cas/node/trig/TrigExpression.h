//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_TRIGFUNCTIONS_H
#define CAS_TRIGFUNCTIONS_H

#include "cas/CAS.h"
#include "cas/node/UnaryExpression.h"

CAS_NAMESPACE

class TrigExpression : public UnaryExpression {
public:
    TrigExpression() = delete;
    ~TrigExpression() override = default;

    bool _equals(Expression* expression) override;

    std::string latex() override;
    std::wstring stringify() override;

protected:
    explicit TrigExpression(const ExpressionProperties& props, Expression* argument);
    bool needsParentheses();
};

CAS_NAMESPACE_END

#endif//CAS_TRIGFUNCTIONS_H
