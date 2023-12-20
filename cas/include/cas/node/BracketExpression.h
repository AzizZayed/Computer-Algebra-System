//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_BRACKETFUNCTION_H
#define CAS_BRACKETFUNCTION_H

#include "UnaryExpression.h"

CAS_NAMESPACE

class BracketExpression : public UnaryExpression {
public:
    BracketExpression() = delete;

    ~BracketExpression() override = default;

    bool _equals(Expression* other) override;

    Expression* derivative(char var) override;

    std::string latex() override;

    std::string str() override;

    std::string text() override;

    std::string explicitText() override;

protected:
    explicit BracketExpression(const ExpressionProperties& properties, Expression* argument,
                               const char* openBracket, const char* closeBracket,
                               const char* openBracketLatex, const char* closeBracketLatex);

protected:
    const char* openBracket;
    const char* closeBracket;

    const char* openBracketLatex;
    const char* closeBracketLatex;
};

CAS_NAMESPACE_END

#endif  //CAS_BRACKETFUNCTION_H
