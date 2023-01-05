//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_INVERSETRIGFUNCTION_H
#define CAS_INVERSETRIGFUNCTION_H

#include "TrigExpression.h"

CAS_NAMESPACE

class InverseTrigExpression : public TrigExpression {
public:
    InverseTrigExpression() = delete;
    ~InverseTrigExpression() override = default;

    std::string latex() override;

protected:
    explicit InverseTrigExpression(const ExpressionProperties& props, ExprPtr argument);
};

CAS_NAMESPACE_END

#endif//CAS_INVERSETRIGFUNCTION_H
