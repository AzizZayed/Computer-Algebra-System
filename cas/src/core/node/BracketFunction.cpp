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

bool BracketFunction::equals(Expression* other) {
    if (this == other)
        return true;

    if (other->getProperties().getType() != properties.getType())
        return false;

    auto* otherBracketFunction = dynamic_cast<BracketFunction*>(other);
    return argument->equals(otherBracketFunction->argument) && wcscmp(openBracket, otherBracketFunction->openBracket) == 0 && wcscmp(closeBracket, otherBracketFunction->closeBracket) == 0;
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