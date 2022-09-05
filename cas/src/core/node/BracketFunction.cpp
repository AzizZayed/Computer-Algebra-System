//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/BracketFunction.h"
#include <sstream>

CAS_NAMESPACE

BracketFunction::BracketFunction(const ExpressionProperties& properties, Expression* argument,
                                 const char* openBracket, const char* closeBracket)
    : FixedInputFunction(properties, argument), openBracket(openBracket), closeBracket(closeBracket) {}

BracketFunction::~BracketFunction() {
    delete openBracket;
    delete closeBracket;
    openBracket = nullptr;
    closeBracket = nullptr;
}

bool BracketFunction::equals(Expression* other) {
    if (this == other)
        return true;

    if (other->getProperties().getType() != properties.getType())
        return false;

    auto* otherBracketFunction = dynamic_cast<BracketFunction*>(other);
    return argument->equals(otherBracketFunction->argument) && strcmp(openBracket, otherBracketFunction->openBracket) == 0 && strcmp(closeBracket, otherBracketFunction->closeBracket) == 0;
}

std::string BracketFunction::latex() {
    return openBracket + argument->latex() + closeBracket;
}

std::string BracketFunction::stringify() {
    return openBracket + argument->stringify() + closeBracket;
}

std::string BracketFunction::text() {
    return openBracket + argument->text() + closeBracket;
}

std::string BracketFunction::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END