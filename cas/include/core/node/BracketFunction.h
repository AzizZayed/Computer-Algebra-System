//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_BRACKETFUNCTION_H
#define CAS_BRACKETFUNCTION_H

#include "FixedInputFunction.h"
#include "core/CAS.h"

CAS_NAMESPACE

class BracketFunction : public FixedInputFunction {
public:
    BracketFunction() = delete;

    ~BracketFunction() override;

    bool equals(Expression *other) override;

    std::string latex() override;

    std::string stringify() override;

    std::string text() override;

    std::string explicitText() override;

protected:
    explicit BracketFunction(const ExpressionProperties &properties, Expression *argument, const char *openBracket,
                             const char *closeBracket);

private:
    const char *openBracket;
    const char *closeBracket;
};

CAS_NAMESPACE_END

#endif//CAS_BRACKETFUNCTION_H
