//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/UnaryFunction.h"
#include "cas/node/Const.h"
#include "cas/node/Var.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

UnaryFunction::UnaryFunction(const ExpressionProperties& properties, Expression* argument)
    : Expression(properties), argument(argument) {
    this->argument->setParent(this);
}

UnaryFunction::~UnaryFunction() {
    delete argument;
    argument = nullptr;
}

Expression* UnaryFunction::derivative(char var) {
    if (argument->isOfType(ExpressionType::CONSTANT))
        return new Const(0);

    if (argument->isOfType(ExpressionType::VARIABLE)) {
        auto* variable = dynamic_cast<Var*>(argument);
        if (variable->getSymbol() != var)
            return new Const(0);
    }

    return _derivative(var);
}

std::string UnaryFunction::latex() {
    return "\\" + properties.getShortName() + "\\left(" + argument->latex() + "\\right)";
}

std::wstring UnaryFunction::stringify() {
    return toWstring(properties.getShortName()) + L"(" + argument->stringify() + L")";
}

std::string UnaryFunction::text() {
    return properties.getShortName() + "(" + argument->text() + ")";
}

std::string UnaryFunction::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END