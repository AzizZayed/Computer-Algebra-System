//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Min.h"

CAS_NAMESPACE

Min::Min(std::vector<Expression*> expressions)
    : NaryExpression({ExpressionType::MIN, "minimum", "min"}, std::move(expressions)) {}

double Min::evaluate(const std::unordered_map<char, double>& variables) {
    auto functor = [variables](Expression* a, Expression* b) {
        return a->evaluate(variables) < b->evaluate(variables);
    };

    return (*std::min_element(expressions.begin(), expressions.end(), functor))->evaluate(variables);
}

Min* Min::clone() {
    std::vector<Expression*> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return new Min(clonedExpressions);
}

Expression* Min::simplified() {
    std::vector<Expression*> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        simplifiedExpressions.push_back(expression->simplified());

    return new Min(simplifiedExpressions);// TODO: Simplify
}

CAS_NAMESPACE_END
