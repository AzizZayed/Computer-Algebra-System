//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "cas/node/Sum.h"
#include "cas/CAS.h"
#include "cas/node/Const.h"
#include "cas/util/StringUtils.h"
#include <sstream>

CAS_NAMESPACE

Sum::Sum(const std::vector<Expression*>& expressions)
    : Operator({ExpressionType::SUM, "summation", "sum"}, 0.0, '+', expressions) {}

Sum::~Sum() {
#if DEBUG_CAS
    wPrint(L"Destroy cas::Sum\n");
#endif
}

Sum* Sum::clone() {
    std::vector<Expression*> clonedExpressions;
    clonedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        clonedExpressions.push_back(expression->clone());

    return new Sum{clonedExpressions};
}

Sum* Sum::derivative(char var) {
    std::vector<Expression*> differentiatedExpressions;
    differentiatedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        differentiatedExpressions.push_back(expression->derivative(var));

    return new Sum{differentiatedExpressions};
}

Expression* Sum::simplified() {
    // TODO: simplify
    std::vector<Expression*> simplifiedExpressions;
    simplifiedExpressions.reserve(expressions.size());

    for (auto& expression: expressions)
        simplifiedExpressions.push_back(expression->simplified());

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
            ss << " " << symbol << " ";

        ss << exp->latex();

        if (needsParens)
            ss << "\\right)";
    }

    return ss.str();
}

std::wstring Sum::stringify() {
    if (expressions.empty())
        return L"";

    std::wstringstream ss;

    for (size_t i = 0; i < expressions.size(); i++) {
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
