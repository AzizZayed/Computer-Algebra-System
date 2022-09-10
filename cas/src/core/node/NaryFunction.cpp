//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#include "cas/node/NaryFunction.h"
#include "cas/util/StringUtils.h"
#include <sstream>

CAS_NAMESPACE

NaryFunction::NaryFunction(const ExpressionProperties& props,
                           std::vector<Expression*> expressions)
    : Expression(props), expressions(std::move(expressions)) {
    for (auto& expression: this->expressions) {
        expression->setParent(this);
    }
}

NaryFunction::~NaryFunction() {
    for (auto& expression: expressions) {
        delete expression;
        expression = nullptr;
    }
}

bool NaryFunction::_equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->isOfType(properties.getType())) {
        auto* function = dynamic_cast<NaryFunction*>(expression);
        if (expressions.size() != function->expressions.size())
            return false;

        for (size_t i = 0; i < expressions.size(); i++)
            if (!expressions[i]->equals(function->expressions[i]))
                return false;

        return true;
    }
    return false;
}

std::string NaryFunction::latex() {
    std::stringstream ss;
    ss << "\\" << properties.getShortName() << "\\left(";
    for (size_t i = 0; i < expressions.size(); i++) {
        ss << expressions[i]->text();
        if (i < expressions.size() - 1)
            ss << ", ";
    }
    ss << "\\right)";
    return ss.str();
}

std::wstring NaryFunction::stringify() {
    std::wstringstream ss;
    ss << toWstring(properties.getShortName()) << L"(";
    for (size_t i = 0; i < expressions.size(); i++) {
        ss << expressions[i]->stringify();
        if (i < expressions.size() - 1)
            ss << ", ";
    }
    ss << L")";
    return ss.str();
}

std::string NaryFunction::text() {
    std::stringstream ss;
    ss << properties.getShortName() << "(";
    for (size_t i = 0; i < expressions.size(); i++) {
        ss << expressions[i]->text();
        if (i < expressions.size() - 1)
            ss << ", ";
    }
    ss << ")";
    return ss.str();
}

std::string NaryFunction::explicitText() {
    std::stringstream ss;
    ss << properties.getShortName() << "(";
    for (size_t i = 0; i < expressions.size(); i++) {
        ss << expressions[i]->explicitText();
        if (i < expressions.size() - 1)
            ss << ", ";
    }
    ss << ")";
    return ss.str();
}

CAS_NAMESPACE_END