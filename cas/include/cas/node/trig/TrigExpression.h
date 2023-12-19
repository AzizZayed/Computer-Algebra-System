//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_TRIGFUNCTIONS_H
#define CAS_TRIGFUNCTIONS_H

#include "cas/CAS.h"
#include "cas/node/UnaryExpression.h"
#include <unordered_map>

CAS_NAMESPACE

struct UnitCircleCoordinate {
    double angle;
    ExprPtr cos;
    ExprPtr sin;
    ExprPtr tan;
};

class TrigExpression : public UnaryExpression {
public:
    TrigExpression() = delete;
    ~TrigExpression() override = default;

    bool _equals(const ExprPtr& expression) override;

    std::string latex() override;
    std::wstring stringify() override;

public:
    static const std::unordered_map<double, UnitCircleCoordinate> unitCircle;

protected:
    explicit TrigExpression(const ExpressionProperties& props, const ExprPtr& argument);
    bool needsParentheses();
};

CAS_NAMESPACE_END

#endif//CAS_TRIGFUNCTIONS_H
