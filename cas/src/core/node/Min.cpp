//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Min.h"
#include "cas/node/Const.h"
#include <algorithm>

CAS_NAMESPACE

Min::Min(std::vector<Expression*> expressions)
    : NaryExpression({ExpressionType::MIN, "minimum", "min"}, std::move(expressions)) {}

double Min::evaluate(const VariableMap& variables) {
    auto functor = [&](Expression* a, Expression* b) {
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
    if (expressions.size() == 1)
        return expressions[0]->simplified();

    std::vector<Expression*> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    std::transform(expressions.begin(), expressions.end(), simplifiedExpressions.begin(), [](Expression* expr) {
        return expr->simplified();
    });

    bool (*isConstant)(Expression*) = [](Expression* expression) {
        return expression->isOfType(ExpressionType::CONSTANT);
    };

    size_t constantCount = std::count_if(simplifiedExpressions.begin(), simplifiedExpressions.end(), isConstant);

    if (constantCount > 1) {
        bool allConstant = std::all_of(simplifiedExpressions.begin(), simplifiedExpressions.end(), isConstant);
        if (allConstant) {
            double minElement = (*std::min_element(simplifiedExpressions.begin(), simplifiedExpressions.end(), [](Expression* a, Expression* b) {
                                    return a->evaluate() < b->evaluate();
                                }))->evaluate();

            return Const::n(minElement);
        }

        std::vector<Expression*> reducedExpressions;
        reducedExpressions.reserve(expressions.size());

        double min = math::POSITIVE_INFINITY;
        for (auto& expr: simplifiedExpressions) {
            if (expr->isOfType(ExpressionType::CONSTANT)) {
                min = std::min(min, expr->evaluate());
            } else {
                reducedExpressions.push_back(expr);
            }
        }
        reducedExpressions.push_back(Const::n(min));

        if (reducedExpressions.size() == 1) {
            return reducedExpressions[0];
        }

        return new Min(reducedExpressions);
    }

    return new Min(simplifiedExpressions);
}

CAS_NAMESPACE_END
