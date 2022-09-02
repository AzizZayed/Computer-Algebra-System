//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "core/CAS.h"
#include "core/node/Sum.h"
#include "core/node/Constant.h"
#include <sstream>

CAS_NAMESPACE

Sum::Sum(cas::Expression *parent, const std::vector<Expression*>& expressions)
: Operator(parent, {ExpressionType::SUM, "summation", "sum"}, '+', expressions) {}

Sum::~Sum()
{
#if DEBUG_CAS
    printf("Destroy cas::Sum\n");
#endif
}

Sum* Sum::clone(cas::Expression* newParent)
{
    std::vector<Expression*> clonedExpressions;

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone(newParent));

    return new Sum{newParent, clonedExpressions};
}

Sum* Sum::derivative(cas::Expression *newParent, char variable)
{
    std::vector<Expression*> differentiatedExpressions;

    for (auto& expression: expressions)
        differentiatedExpressions.push_back(expression->derivative(newParent, variable));

    return new Sum{newParent, differentiatedExpressions};
}

Expression* Sum::simplified(Expression* newParent)
{
    // TODO: simplify
    std::vector<Expression*> simplifiedExpressions;

    for (auto& expression: expressions)
        simplifiedExpressions.push_back(expression->simplified(newParent));

    return new Sum{newParent, simplifiedExpressions};
}

double Sum::operate(double a, double b)
{
    return a + b;
}

double Sum::neutral()
{
    return 0.0;
}

bool Sum::needsParentheses(Expression* expression)
{
    return false;
}

std::string Sum::latex()
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
        if (i > 0 && !exp->isNegated())
            ss << " " << symbol << " ";

        ss << exp->latex();

        if (needsParens)
            ss << "\\right)";
    }

    return ss.str();
}

std::string Sum::stringify()
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
        if (i > 0 && !exp->isNegated())
            ss << " " << symbol << " ";

        ss << exp->stringify();

        if (needsParens)
            ss << ")";
    }

    return ss.str();
}

CAS_NAMESPACE_END
