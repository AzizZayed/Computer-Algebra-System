//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "cas/node/Product.h"
#include "cas/node/Const.h"
#include "cas/node/Sum.h"
#include <sstream>

CAS_NAMESPACE

Product::Product(const std::vector<Expression*>& expressions)
    : Operator({ExpressionType::PRODUCT, "product", "prod"}, 1.0, '*', expressions) {}

Product* Product::clone() {
    std::vector<Expression*> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return new Product {clonedExpressions};
}

Expression* Product::_derivative(char var) {
    std::vector<Expression*> differentiatedExpressions;
    differentiatedExpressions.reserve(expressions.size());

    for (size_t i = 0; i < expressions.size(); i++) {
        std::vector<Expression*> products;
        products.reserve(expressions.size());
        for (size_t j = 0; j < expressions.size(); j++) {
            Expression* exp = expressions[j];
            Expression* prod = i == j ? exp->derivative(var) : exp->clone();
            products.push_back(prod);
        }
        differentiatedExpressions.push_back(new Product {products});
    }

    return new Sum {differentiatedExpressions};
}

Expression* Product::simplified() {
    // TODO: simplify

    // If there is only one expression, return it
    if (expressions.size() == 1)
        return expressions[0]->simplified();

    std::vector<Expression*> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    double constant = 1.0;
    for (auto& expression: expressions) {
        Expression* x = expression->simplified();

        if (x->isOfType(ExpressionType::CONSTANT)) {
            double value = x->evaluate();
            if (value == 0) {
                delete x;
                return Const::zero();
            }
            constant *= value;
            continue;
        } else if (x->isOfType(ExpressionType::PRODUCT)) {
            auto* product = dynamic_cast<Product*>(x);
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

    std::sort(simplifiedExpressions.begin(), simplifiedExpressions.end(), [](Expression* a, Expression* b) {
        return a->lessThan(b);
    });
    return new Product {simplifiedExpressions};
}

bool Product::needsParentheses(Expression* expression) {
    return expression->getProperties().getType() == ExpressionType::SUM;
}

std::string Product::latex() {
    if (expressions.empty())
        return "";

    std::stringstream ss;

    for (size_t i = 0; i < expressions.size(); i++) {
        Expression* exp = expressions[i];
        bool needsParens = needsParentheses(exp);

        if (needsParens)
            ss << "\\left(";

        // If 2 consecutive constants, add the symbol between them if they are not symbols
        if (i > 0 && expressions[i - 1]->isOfType(ExpressionType::CONSTANT) && exp->isOfType(ExpressionType::CONSTANT)) {
            auto* a = dynamic_cast<Const*>(expressions[i - 1]);
            auto* b = dynamic_cast<Const*>(exp);

            if (!a->isSymbol() && !b->isSymbol())
                ss << symbol;
        }

        ss << exp->latex();

        if (needsParens)
            ss << "\\right)";
    }

    return ss.str();
}

std::string Product::str() {
    if (expressions.empty())
        return "";

    std::stringstream ss;

    for (size_t i = 0; i < expressions.size(); i++) {
        Expression* exp = expressions[i];
        bool needsParens = needsParentheses(exp);

        if (needsParens)
            ss << "(";
        if (i > 0)
            ss << " " << symbol << " ";

        ss << exp->str();

        if (needsParens)
            ss << ")";
    }

    return ss.str();
}

CAS_NAMESPACE_END
