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

    //    std::string latex() override;

protected:
    explicit InverseTrigFunction(const ExpressionProperties& props, Expression* argument);
};

CAS_NAMESPACE_END

#endif//CAS_INVERSETRIGFUNCTION_H
