//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "core/node/Product.h"
#include "core/CAS.h"
#include "core/node/Sum.h"
#include <sstream>

CAS_NAMESPACE

Product::Product(Expression* parent, const std::vector<Expression*>& expressions)
: Operator(parent, {ExpressionType::PRODUCT, "product", "prod"}, '*',expressions) {}

Product::~Product()
{
#if DEBUG_CAS
    printf("Destroy cas::Product\n");
#endif
}

Product* Product::clone(Expression* newParent)
{
    std::vector<Expression*> clonedExpressions;

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone(newParent));

    return new Product{newParent, clonedExpressions};
}

Expression* Product::derivative(Expression* newParent, char variable)
{
    std::vector<Expression*> differentiatedExpressions;
    
    for (size_t i = 0; i < expressions.size(); i++)
    {
        std::vector<Expression*> products;
        for (size_t j = 0; j < expressions.size(); j++) {
            Expression* exp = expressions[j];

            Expression* derivative = exp->derivative(nullptr, variable);
            Expression* clone = exp->clone(nullptr);

            Expression* prod = i == j ? derivative : clone;
            products.push_back(prod);
        }
        differentiatedExpressions.push_back(new Product{nullptr, products});
    }

    return new Sum{newParent, differentiatedExpressions};
}

Expression* Product::simplified(Expression* newParent)
{
    // TODO: simplify
    std::vector<Expression*> simplifiedExpressions;

    for (auto& expression: expressions)
        simplifiedExpressions.push_back(expression->simplified(newParent));

    return new Sum{newParent, simplifiedExpressions};
}

double Product::operate(double a, double b)
{
    return a * b;
}

double Product::neutral()
{
    return 1.0;
}

bool Product::needsParentheses(Expression* expression)
{
    return expression->getProperties().getType() == ExpressionType::SUM;
}

std::string Product::latex()
{
    if (expressions.empty())
        return "";

    std::stringstream ss;

    for (size_t i = 0; i < expressions.size(); i++)
    {
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

std::string Product::stringify()
{
    if (expressions.empty())
        return "";

    std::stringstream ss;

    for (size_t i = 0; i < expressions.size(); i++)
    {
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
