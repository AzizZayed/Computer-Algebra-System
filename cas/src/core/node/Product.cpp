//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "cas/node/Product.h"
#include "cas/node/Sum.h"
#include "cas/util/StringUtils.h"
#include <sstream>

CAS_NAMESPACE

Product::Product(const std::vector<Expression*>& expressions)
    : Operator({ExpressionType::PRODUCT, "product", "prod"}, 1.0, '*', expressions) {}

Product::~Product() {
#if DEBUG_CAS
    wPrint(L"Destroy cas::Product\n");
#endif
}

Product* Product::clone() {
    std::vector<Expression*> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return new Product{clonedExpressions};
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
        differentiatedExpressions.push_back(new Product{products});
    }

    return new Sum{differentiatedExpressions};
}

Expression* Product::simplified() {
    // TODO: simplify
    std::vector<Expression*> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        simplifiedExpressions.push_back(expression->simplified());

    return new Sum{simplifiedExpressions};
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
        if (i > 0)
            ss << " " << symbol << " ";

        ss << exp->latex();

        if (needsParens)
            ss << "\\right)";
    }

    return ss.str();
}

std::wstring Product::stringify() {
    if (expressions.empty())
        return L"";

    std::wstringstream ss;

    for (size_t i = 0; i < expressions.size(); i++) {
        Expression* exp = expressions[i];
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
