//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#include "core/node/MultipleInputFunction.h"
#include "../../util/StringUtils.h"
#include "core/CAS.h"
#include "core/node/Expression.h"
#include <sstream>

CAS_NAMESPACE

MultipleInputFunction::MultipleInputFunction(const ExpressionProperties& props,
                                             std::vector<Expression*> expressions)
    : Expression(props), expressions(std::move(expressions)) {
    for (auto& expression: this->expressions) {
        expression->setParent(this);
    }
}

MultipleInputFunction::~MultipleInputFunction() {
    for (auto& expression: expressions) {
        delete expression;
        expression = nullptr;
    }
}

bool MultipleInputFunction::equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->isOfType(properties.getType())) {
        auto* function = dynamic_cast<MultipleInputFunction*>(expression);
        if (expressions.size() != function->expressions.size())
            return false;

        for (size_t i = 0; i < expressions.size(); i++)
            if (!expressions[i]->equals(function->expressions[i]))
                return false;

        return true;
    }
    return false;
}

std::string MultipleInputFunction::latex() {
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

std::wstring MultipleInputFunction::stringify() {
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

std::string MultipleInputFunction::text() {
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

std::string MultipleInputFunction::explicitText() {
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