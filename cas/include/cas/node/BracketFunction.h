//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_BRACKETFUNCTION_H
#define CAS_BRACKETFUNCTION_H

#include "UnaryFunction.h"
#include "cas/CAS.h"

CAS_NAMESPACE

class BracketFunction : public UnaryFunction {
public:
    BracketFunction() = delete;

    ~BracketFunction() override = default;

    bool _equals(Expression* other) override;

    Expression* derivative(char var) override;

    std::string latex() override;

    std::wstring stringify() override;

    std::string text() override;

    std::string explicitText() override;

protected:
    explicit BracketFunction(const ExpressionProperties& properties, Expression* argument,
                             const wchar_t* openBracket, const wchar_t* closeBracket,
                             const char* openBracketLatex, const char* closeBracketLatex);

protected:
    const wchar_t* openBracket;
    const wchar_t* closeBracket;

    const char* openBracketLatex;
    const char* closeBracketLatex;
};

CAS_NAMESPACE_END

#endif//CAS_BRACKETFUNCTION_H
