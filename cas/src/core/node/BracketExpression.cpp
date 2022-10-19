//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/BracketExpression.h"
#include <stdexcept>

CAS_NAMESPACE

BracketExpression::BracketExpression(const ExpressionProperties& properties, Expression* argument,
                                     const wchar_t* openBracket, const wchar_t* closeBracket,
                                     const char* openBracketLatex, const char* closeBracketLatex)
    : UnaryExpression(properties, argument),
      openBracket(openBracket), closeBracket(closeBracket),
      openBracketLatex(openBracketLatex), closeBracketLatex(closeBracketLatex) {}

bool BracketExpression::_equals(Expression* other) {
    auto* otherBracketFunction = dynamic_cast<BracketExpression*>(other);
    return argument->equals(otherBracketFunction->argument);
}

Expression* BracketExpression::derivative(char) {
    throw std::runtime_error("The " + properties.getName() + "::derivative() operation is not supported");
}

std::string BracketExpression::latex() {
    return openBracketLatex + argument->latex() + closeBracketLatex;
}

std::wstring BracketExpression::stringify() {
    return openBracket + argument->stringify() + closeBracket;
}

std::string BracketExpression::text() {
    return properties.getShortName() + "[" + argument->text() + "]";
}

std::string BracketExpression::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END
