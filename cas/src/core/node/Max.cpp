//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "core/node/Max.h"
#include <utility>

CAS_NAMESPACE

Max::Max(std::vector<Expression *> expressions)
    : MultipleInputFunction({ExpressionType::MAX, "maximum", "max"}, std::move(expressions)) {}

double Max::evaluate(const std::unordered_map<char, double> &variables) {
    auto functor = [variables](Expression *a, Expression *b) {
        return a->evaluate(variables) > b->evaluate(variables);
    };

    return (*std::max_element(expressions.begin(), expressions.end(), functor))->evaluate(variables);
}

Max *Max::clone() {
    std::vector<Expression *> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto &expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return new Max(clonedExpressions);
}

Expression *Max::simplified() {
    std::vector<Expression *> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    for (auto &expression: expressions)
        simplifiedExpressions.push_back(expression->simplified());

    return new Max(simplifiedExpressions);// TODO: Simplify
}

CAS_NAMESPACE_END