//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_INVERSETRIGFUNCTION_H
#define CAS_INVERSETRIGFUNCTION_H

#include "TrigFunction.h"

CAS_NAMESPACE

class InverseTrigFunction : public TrigFunction {
public:
    InverseTrigFunction() = delete;
    ~InverseTrigFunction() override = default;

    std::string latex() override {
        if (needsParentheses())
            return "\\" + properties.getShortName() + "^{-1}{\\left(" + argument->latex() + "\\right)}";
        return "\\" + properties.getShortName() + "^{-1}{" + argument->latex() + "}";
    }

protected:
    explicit InverseTrigFunction(const ExpressionProperties& props, Expression* argument)
        : TrigFunction(props, argument) {}
};

CAS_NAMESPACE_END

#endif//CAS_INVERSETRIGFUNCTION_H
