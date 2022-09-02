//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "core/CAS.h"
#include "core/node/Variable.h"

CAS_NAMESPACE

Variable::Variable(Expression* parent, char variable)
: symbol(variable), Expression(parent, {ExpressionType::VARIABLE, "variable", "var"})
{
#if DEBUG_CAS
    printf("%s(%c)\n", properties.getName().c_str(), variable);
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
    if (variables.find(symbol) == variables.end())
        throw std::runtime_error("Variable not found for evaluation");
    return variables.at(symbol);
}

bool Variable::equals(Expression* expression)
{
    if (expression->getProperties().getType() == ExpressionType::VARIABLE)
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
    return explicitText();
}

std::string Variable::explicitText()
{
    return std::string{symbol};
}

CAS_NAMESPACE_END