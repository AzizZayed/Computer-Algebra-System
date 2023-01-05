//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Min.h"
#include "cas/node/Const.h"
#include <algorithm>

CAS_NAMESPACE

Min::Min(std::vector<ExprPtr> expressions)
    : NaryExpression({ExpressionType::MIN, "minimum", "min"}, std::move(expressions)) {}

double Min::evaluate(const VariableMap& variables) {
    auto functor = [&](ExprPtr a, ExprPtr b) {
        return a->evaluate(variables) < b->evaluate(variables);
    };

    return (*std::min_element(expressions.begin(), expressions.end(), functor))->evaluate(variables);
}

ExprPtr Min::clone() {
    std::vector<ExprPtr> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return Min::from(clonedExpressions);
}

ExprPtr Min::simplified() {
    if (expressions.size() == 1)
        return expressions[0]->simplified();

    std::vector<ExprPtr> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    std::transform(expressions.begin(), expressions.end(), simplifiedExpressions.begin(), [](ExprPtr expr) {
        return expr->simplified();
    });

    bool (*isConstant)(ExprPtr) = [](ExprPtr expression) {
        return expression->isOfType(ExpressionType::CONSTANT);
    };

    size_t constantCount = std::count_if(simplifiedExpressions.begin(), simplifiedExpressions.end(), isConstant);

    if (constantCount > 1) {
        bool allConstant = std::all_of(simplifiedExpressions.begin(), simplifiedExpressions.end(), isConstant);
        if (allConstant) {
            double minElement = (*std::min_element(simplifiedExpressions.begin(), simplifiedExpressions.end(), [](ExprPtr a, ExprPtr b) {
                                    return a->evaluate() < b->evaluate();
                                }))->evaluate();

            return Const::n(minElement);
        }

        std::vector<ExprPtr> reducedExpressions;
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

        return Min::from(reducedExpressions);
    }

    return Min::from(simplifiedExpressions);
}

CAS_NAMESPACE_END
