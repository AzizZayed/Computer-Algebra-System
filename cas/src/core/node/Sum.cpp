//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "cas/node/Sum.h"
#include "cas/node/Const.h"
#include <sstream>
#include <algorithm>

CAS_NAMESPACE

Sum::Sum(const std::vector<Expression*>& expressions)
    : Operator({ExpressionType::SUM, "summation", "sum"}, 0.0, '+', expressions) {}

Sum* Sum::clone() {
    std::vector<Expression*> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return new Sum{clonedExpressions};
}

Sum* Sum::_derivative(char var) {
    std::vector<Expression*> differentiatedExpressions;
    differentiatedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        differentiatedExpressions.push_back(expression->derivative(var));

    return new Sum{differentiatedExpressions};
}

Expression* Sum::simplified() {
    // TODO: simplify

    // If there is only one expression, return it
    if (expressions.size() == 1)
        return expressions[0]->simplified();

    std::vector<Expression*> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    double constant = 0.0;
    for (auto& expression: expressions) {
        Expression* x = expression->simplified();

        if (x->isOfType(ExpressionType::CONSTANT)) {
            double value = x->evaluate();
            if (value == 0.0) {
                delete x;
                continue;
            }
            constant += value;
            continue;
        } else if (x->isOfType(ExpressionType::SUM)) {
            auto* sum = dynamic_cast<Sum*>(x);
            for (auto& exp: sum->expressions)
                simplifiedExpressions.push_back(exp);
            continue;
        }

        simplifiedExpressions.push_back(x);
    }
    if (constant != 0.0)
        simplifiedExpressions.push_back(Const::n(constant));

    if (simplifiedExpressions.size() == 1)
        return simplifiedExpressions[0];

    std::sort(simplifiedExpressions.begin(), simplifiedExpressions.end());
    return new Sum{simplifiedExpressions};
}

std::string Sum::latex() {
    if (expressions.empty())
        return "";

    std::stringstream ss;

    for (size_t i = 0; i < expressions.size(); i++) {
        Expression* exp = expressions[i];
        bool needsParens = needsParentheses(exp);

        if (needsParens)
            ss << "\\left(";
        if (i > 0 && !exp->isNegated())
            ss << symbol;

        ss << exp->latex();

        if (needsParens)
            ss << "\\right)";
    }

    return ss.str();
}

std::string Sum::str() {
    if (expressions.empty())
        return "";

    std::stringstream ss;

    for (size_t i = 0; i < expressions.size(); i++) {
        Expression* exp = expressions[i];
        bool needsParens = needsParentheses(exp);

        if (needsParens)
            ss << "(";
        if (i > 0 && !exp->isNegated())
            ss << " " << symbol << " ";

        ss << exp->str();

        if (needsParens)
            ss << ")";
    }

    return ss.str();
}

CAS_NAMESPACE_END
