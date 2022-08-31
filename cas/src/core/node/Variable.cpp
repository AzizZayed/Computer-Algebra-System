//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "core/CAS.h"
#include "core/node/Variable.h"

CAS_NAMESPACE

Variable::Variable(Expression* parent, char variable)
: symbol(variable), Expression(parent, ExpressionType::VARIABLE)
{
#if DEBUG_CAS
    std::string str = stringifyExpressionType(expressionType);
    printf("%s(%c)\n", str.c_str(), variable);
#endif
}

Variable::~Variable()
{
#if DEBUG_CAS
    printf("Destroy cas::Variable\n");
#endif
}

Variable* Variable::clone(Expression* newParent)
{
    return new Variable{newParent, symbol};
}

double Variable::evaluate(const std::unordered_map<char, double>& variables)
{
    return variables.at(symbol);
}

bool Variable::equals(Expression* expression)
{
    if (expression->getExpressionType() == ExpressionType::VARIABLE)
    {
        auto* var = dynamic_cast<Variable*>(expression);
        return var->getSymbol() == symbol;
    }
    return false;
}

Constant* Variable::derivative(Expression* newParent, char var)
{
    double derivative = symbol == var ? 1.0 : 0.0;
    return new Constant{newParent, derivative};
}

Variable* Variable::simplified(Expression* newParent)
{
    return clone(newParent);
}

std::string Variable::latex()
{
    return text();
}

std::string Variable::stringify()
{
    return text();
}

std::string Variable::text()
{
    return fullText();
}

std::string Variable::fullText()
{
    return std::string{symbol};
}

CAS_NAMESPACE_END