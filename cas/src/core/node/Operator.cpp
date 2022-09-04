//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "core/node/Operator.h"

#include <utility>
#include <sstream>

CAS_NAMESPACE

Operator::Operator(const ExpressionProperties& props, double neutral, char symbol, std::vector<Expression*> expressions)
: neutral(neutral), symbol(symbol), expressions(std::move(expressions)), Expression(props)
{
#if DEBUG_CAS
    printf("%s(%c...)\n", properties.getName().c_str(), symbol);
#endif

    for (auto& expression: this->expressions)
        expression->setParent(this);
}

Operator::~Operator()
{
    for (size_t i = 0; i < expressions.size(); i++) {
        delete expressions[i];
        expressions[i] = nullptr;
    }
}

double Operator::evaluate(const std::unordered_map<char, double>& variables)
{
    double result = neutral;
    for (auto* expression: expressions)
        result = operate(result, expression->evaluate(variables));

    return result;
}

bool Operator::equals(Expression* expression)
{
    if (this == expression)
        return true;

    if (!isOfSameType(expression))
        return false;

    auto* op = dynamic_cast<Operator*>(expression);

    if (expressions.size() != op->expressions.size() || symbol != op->getSymbol())
        return false;

    bool equalExpressions = true;
    for (size_t i = 0; i < expressions.size(); i++)
        equalExpressions = equalExpressions && expressions[i]->equals(op->expressions[i]);

    return equalExpressions;
}

std::string Operator::text()
{
    if (expressions.empty())
        return "";

    std::stringstream ss;

    ss << "((" << expressions[0]->text() << ") ";
    for (size_t i = 1; i < expressions.size() - 1; i++)
        ss << symbol << " (" << expressions[i]->text() << ") ";
    ss << symbol << " (" << expressions[expressions.size() - 1]->text() << "))";

    return ss.str();
}

std::string Operator::explicitText()
{
    if (expressions.empty())
        return "";

    std::stringstream ss;

    ss << properties.getShortName() << "(";
    for (size_t i = 0; i < expressions.size() - 1; i++)
        ss << expressions[i]->explicitText() << ", ";
    ss << expressions[expressions.size() - 1]->explicitText() << ")";

    return ss.str();
}

CAS_NAMESPACE_END
