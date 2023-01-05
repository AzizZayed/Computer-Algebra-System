//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "cas/node/Const.h"
#include "cas/node/Prod.h"
#include "cas/node/Sum.h"
#include <sstream>

CAS_NAMESPACE

Prod::Prod(const std::vector<ExprPtr>& expressions)
    : Operator({ExpressionType::PRODUCT, "product", "prod"}, 1.0, '*', expressions) {}

ExprPtr Prod::clone() {
    std::vector<ExprPtr> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return Prod::from({clonedExpressions});
}

ExprPtr Prod::_derivative(char var) {
    std::vector<ExprPtr> differentiatedExpressions;
    differentiatedExpressions.reserve(expressions.size());

    for (size_t i = 0; i < expressions.size(); i++) {
        std::vector<ExprPtr> products;
        products.reserve(expressions.size());
        for (size_t j = 0; j < expressions.size(); j++) {
            ExprPtr exp = expressions[j];
            ExprPtr prod = i == j ? exp->derivative(var) : exp->clone();
            products.push_back(prod);
        }
        differentiatedExpressions.push_back(Prod::from({products}));
    }

    return Sum::from({differentiatedExpressions});
}

ExprPtr Prod::simplified() {
    // TODO: simplify

    // If there is only one expression, return it
    if (expressions.size() == 1)
        return expressions[0]->simplified();

    std::vector<ExprPtr> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    double constant = 1.0;
    for (auto& expression: expressions) {
        ExprPtr x = expression->simplified();

        if (x->isOfType(ExpressionType::CONSTANT)) {
            double value = x->evaluate();
            if (value == 0) {
                return Const::zero();
            }
            constant *= value;
            continue;
        } else if (x->isOfType(ExpressionType::PRODUCT)) {
            auto* product = dynamic_cast<Prod*>(x.get());
            for (auto& exp: product->expressions)
                simplifiedExpressions.push_back(exp);
            continue;
        }

        simplifiedExpressions.push_back(x);
    }
    if (constant != 1.0)
        simplifiedExpressions.push_back(Const::n(constant));

    if (simplifiedExpressions.size() == 1)
        return simplifiedExpressions[0];

    std::sort(simplifiedExpressions.begin(), simplifiedExpressions.end(), [](ExprPtr a, ExprPtr b) {
        return a->lessThan(b);
    });
    return Prod::from({simplifiedExpressions});
}

bool Prod::needsParentheses(ExprPtr expression) {
    return expression->getProperties().getType() == ExpressionType::SUM;
}

std::string Prod::latex() {
    if (expressions.empty())
        return "";

    std::stringstream ss;

    for (size_t i = 0; i < expressions.size(); i++) {
        ExprPtr exp = expressions[i];
        bool needsParens = needsParentheses(exp);

        if (needsParens)
            ss << "\\left(";

        // If 2 consecutive constants, add the symbol between them
        if (i > 0 && expressions[i - 1]->isOfType(ExpressionType::CONSTANT) && exp->isOfType(ExpressionType::CONSTANT))
            ss << symbol;

        ss << exp->latex();

        if (needsParens)
            ss << "\\right)";
    }

    return ss.str();
}

std::wstring Prod::stringify() {
    if (expressions.empty())
        return L"";

    std::wstringstream ss;

    for (size_t i = 0; i < expressions.size(); i++) {
        ExprPtr exp = expressions[i];
        bool needsParens = needsParentheses(exp);

        if (needsParens)
            ss << "(";
        if (i > 0)
            ss << " " << symbol << " ";

        ss << exp->stringify();

        if (needsParens)
            ss << ")";
    }

    return ss.str();
}

CAS_NAMESPACE_END
