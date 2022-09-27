//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#include "cas/node/NaryExpression.h"
#include "cas/util/StringUtils.h"
#include <sstream>

CAS_NAMESPACE

NaryExpression::NaryExpression(const ExpressionProperties& props,
                               std::vector<Expression*> expressions)
    : Expression(props), expressions(std::move(expressions)) {
    for (auto& expression: this->expressions) {
        expression->setParent(this);
    }
}

NaryExpression::~NaryExpression() {
    for (auto& expression: expressions) {
        delete expression;
        expression = nullptr;
    }
}

bool NaryExpression::_equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->isOfType(properties.getType())) {
        auto* function = dynamic_cast<NaryExpression*>(expression);
        if (expressions.size() != function->expressions.size())
            return false;

        for (size_t i = 0; i < expressions.size(); i++)
            if (!expressions[i]->equals(function->expressions[i]))
                return false;

        return true;
    }
    return false;
}

std::string NaryExpression::latex() {
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

std::wstring NaryExpression::stringify() {
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

std::string NaryExpression::text() {
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

std::string NaryExpression::explicitText() {
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