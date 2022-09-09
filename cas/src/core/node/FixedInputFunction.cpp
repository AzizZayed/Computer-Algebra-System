//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/FixedInputFunction.h"
#include "cas/util/StringUtils.h"

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
    return "\\" + properties.getShortName() + "\\left(" + argument->latex() + "\\right)";
}

std::wstring FixedInputFunction::stringify() {
    return toWstring(properties.getShortName()) + L"(" + argument->stringify() + L")";
}

std::string FixedInputFunction::text() {
    return properties.getShortName() + "(" + argument->text() + ")";
}

std::string FixedInputFunction::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END