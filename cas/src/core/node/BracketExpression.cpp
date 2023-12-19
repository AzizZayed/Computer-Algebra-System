//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/BracketExpression.h"
#include "fmt/format.h"
#include <stdexcept>

CAS_NAMESPACE

BracketExpression::BracketExpression(const ExpressionProperties& properties, Expression* argument,
                                     const char* openBracket, const char* closeBracket,
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
    return fmt::format("{} {} {}", openBracketLatex, argument->latex(), closeBracketLatex);
}

std::string BracketExpression::str() {
    return openBracket + argument->str() + closeBracket;
}

std::string BracketExpression::text() {
    return properties.getShortName() + "[" + argument->text() + "]";
}

std::string BracketExpression::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END
