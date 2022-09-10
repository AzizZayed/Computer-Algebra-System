//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/BracketFunction.h"
#include <sstream>

CAS_NAMESPACE

BracketFunction::BracketFunction(const ExpressionProperties& properties, Expression* argument,
                                 const wchar_t* openBracket, const wchar_t* closeBracket,
                                 const char* openBracketLatex, const char* closeBracketLatex)
    : UnaryFunction(properties, argument),
      openBracket(openBracket), closeBracket(closeBracket),
      openBracketLatex(openBracketLatex), closeBracketLatex(closeBracketLatex) {}

bool BracketFunction::_equals(Expression* other) {
    auto* otherBracketFunction = dynamic_cast<BracketFunction*>(other);
    return argument->equals(otherBracketFunction->argument) && wcscmp(openBracket, otherBracketFunction->openBracket) == 0 && wcscmp(closeBracket, otherBracketFunction->closeBracket) == 0;
}

Expression* BracketFunction::derivative(char var) {
    throw std::runtime_error("The " + properties.getName() + "::derivative() operation is not supported");
}

std::string BracketFunction::latex() {
    return openBracketLatex + argument->latex() + closeBracketLatex;
}

std::wstring BracketFunction::stringify() {
    return openBracket + argument->stringify() + closeBracket;
}

std::string BracketFunction::text() {
    return properties.getShortName() + "[" + argument->text() + "]";
}

std::string BracketFunction::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END