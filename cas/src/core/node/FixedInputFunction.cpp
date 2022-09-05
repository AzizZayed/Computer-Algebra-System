//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/FixedInputFunction.h"

CAS_NAMESPACE

FixedInputFunction::FixedInputFunction(const ExpressionProperties& properties, Expression* argument)
    : Expression(properties), argument(argument) {
    this->argument->setParent(this);
}

FixedInputFunction::~FixedInputFunction() {
    delete argument;
    argument = nullptr;
}

std::string FixedInputFunction::latex() {
    return properties.getShortName() + "\\left(" + argument->latex() + "\\right)";
}

std::string FixedInputFunction::stringify() {
    return properties.getShortName() + "(" + argument->stringify() + ")";
}

std::string FixedInputFunction::text() {
    return properties.getShortName() + "(" + argument->text() + ")";
}

std::string FixedInputFunction::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END