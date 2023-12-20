#include "cas/node/Max.h"
#include "cas/node/Const.h"
#include <algorithm>

CAS_NAMESPACE

Max::Max(const std::vector<Expression*>& expressions)
    : NaryExpression({ExpressionType::MAX, "maximum", "max"}, expressions) {
    if (expressions.empty())
        throw std::runtime_error("Max must have at least one expression (got 0)");
}

double Max::evaluate(const VariableMap& variables) {
    auto functor = [&](Expression* a, Expression* b) {
        return a->evaluate(variables) > b->evaluate(variables);
    };

    return (*std::max_element(expressions.begin(), expressions.end(), functor))->evaluate(variables);
}

Max* Max::clone() {
    std::vector<Expression*> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (Expression* expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return new Max(clonedExpressions);
}

Expression* Max::simplified() {
    if (expressions.size() == 1)
        return expressions[0]->simplified();

    std::vector<Expression*> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());
    for (Expression* expression: expressions) {
        simplifiedExpressions.push_back(expression->simplified());
    }

    bool (*isConstant)(Expression*) = [](Expression* expression) {
        return expression->isOfType(ExpressionType::CONSTANT);
    };

    size_t constantCount = std::count_if(simplifiedExpressions.begin(), simplifiedExpressions.end(), isConstant);

    if (constantCount > 1) {
        bool allConstant = std::all_of(simplifiedExpressions.begin(), simplifiedExpressions.end(), isConstant);
        if (allConstant) {
            Expression* maxElement = *std::max_element(simplifiedExpressions.begin(), simplifiedExpressions.end(), [](Expression* a, Expression* b) {
                return a->evaluate() > b->evaluate();
            });
            return Const::n(maxElement->evaluate());
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