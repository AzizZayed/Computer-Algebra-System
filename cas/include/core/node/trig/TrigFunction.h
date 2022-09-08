//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_TRIGFUNCTIONS_H
#define CAS_TRIGFUNCTIONS_H

#include "core/CAS.h"
#include "core/node/FixedInputFunction.h"

CAS_NAMESPACE

class TrigFunction : public FixedInputFunction {
public:
    TrigFunction() = delete;
    ~TrigFunction() override = default;

    bool equals(Expression* expression) override;

    std::string latex() override;
    std::wstring stringify() override;

protected:
    explicit TrigFunction(const ExpressionProperties& props, Expression* argument);
    bool needsParentheses();
};

CAS_NAMESPACE_END

#endif//CAS_TRIGFUNCTIONS_H
