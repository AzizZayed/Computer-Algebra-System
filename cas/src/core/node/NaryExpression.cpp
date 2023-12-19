//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#include "cas/node/NaryExpression.h"
#include "cas/util/StringUtils.h"
#include <algorithm>
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
    std::string (*strExp)(Expression*) = [](Expression* expr) { return expr->latex(); };
    return toString("\\" + properties.getShortName(), "{\\left(", ",", "\\right)}", strExp);
}

std::string NaryExpression::str() {
    std::string (*strExp)(Expression*) = [](Expression* expr) { return expr->str(); };
    return toString(properties.getShortName(), "(", ", ", ")", strExp);
}

std::string NaryExpression::text() {
    std::string (*strExp)(Expression*) = [](Expression* expr) { return expr->text(); };
    return toString(properties.getShortName(), "(", ", ", ")", strExp);
}

std::string NaryExpression::explicitText() {
    std::string (*strExp)(Expression*) = [](Expression* expr) { return expr->explicitText(); };
    return toString(properties.getShortName(), "(", ", ", ")", strExp);
}

template<typename F>
std::string NaryExpression::toString(const std::string& name, const char* start, const char* delimiter, const char* end, F&& function) {
    std::stringstream ss;
    ss << name << start;
    for (size_t i = 0; i < expressions.size(); i++) {
        ss << function(expressions[i]);
        if (i < expressions.size() - 1)
            ss << delimiter;
    }
    ss << end;
    return ss.str();
}

template<typename F>
void NaryExpression::forEach(F&& function) const {
    std::for_each(expressions.begin(), expressions.end(), function);
}

template<typename F>
bool NaryExpression::any(F&& function) const {
    return std::any_of(expressions.begin(), expressions.end(), function);
}

template<typename F>
bool NaryExpression::all(F&& function) const {
    return std::all_of(expressions.begin(), expressions.end(), function);
}

CAS_NAMESPACE_END