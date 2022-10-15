//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Max.h"
#include "cas/node/Const.h"

CAS_NAMESPACE

Max::Max(std::vector<Expression*> expressions)
    : NaryExpression({ExpressionType::MAX, "maximum", "max"}, std::move(expressions)) {}

double Max::evaluate(const std::unordered_map<char, double>& variables) {
    auto functor = [variables](Expression* a, Expression* b) {
        return a->evaluate(variables) > b->evaluate(variables);
    };

    return (*std::max_element(expressions.begin(), expressions.end(), functor))->evaluate(variables);
}

Max* Max::clone() {
    std::vector<Expression*> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return new Max(clonedExpressions);
}

Expression* Max::simplified() {
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
            double maxElement = (*std::max_element(simplifiedExpressions.begin(), simplifiedExpressions.end(), [](Expression* a, Expression* b) {
                return a->evaluate() > b->evaluate();
            }))->evaluate();

            return Const::n(maxElement);
        }

        std::vector<Expression*> reducedExpressions;
        reducedExpressions.reserve(expressions.size());

        double max = -1.0 / 0.0;
        for (auto& expr: simplifiedExpressions) {
            if (expr->isOfType(ExpressionType::CONSTANT)) {
                max = std::max(max, expr->evaluate());
            } else {
                reducedExpressions.push_back(expr->simplified());
            }
        }
        reducedExpressions.push_back(Const::n(max));

        if (reducedExpressions.size() == 1) {
            return reducedExpressions[0];
        }

        return new Max(reducedExpressions);
    }

    return new Max(simplifiedExpressions);
}

CAS_NAMESPACE_END