//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "core/node/Variable.h"
#include "core/CAS.h"

CAS_NAMESPACE

Variable::Variable(char variable)
    : symbol(variable), Expression({ExpressionType::VARIABLE, "variable", "var"}) {
#if DEBUG_CAS
    printf("%s(%c)\n", properties.getName().c_str(), variable);
#endif
}

Variable::~Variable() {
#if DEBUG_CAS
    printf("Destroy cas::Variable\n");
#endif
}

Variable* Variable::clone() {
    return new Variable(symbol);
}

double Variable::evaluate(const std::unordered_map<char, double>& variables) {
    if (variables.find(symbol) == variables.end())
        throw std::runtime_error("Variable not found for evaluation");
    return variables.at(symbol);
}

bool Variable::equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->getProperties().getType() == ExpressionType::VARIABLE) {
        auto* var = dynamic_cast<Variable*>(expression);
        return var->getSymbol() == symbol;
    }
    return false;
}

Constant* Variable::derivative(char var) {
    double derivative = symbol == var ? 1.0 : 0.0;
    return new Constant{derivative};
}

Variable* Variable::simplified() {
    return clone();
}

std::string Variable::latex() {
    return text();
}

std::string Variable::stringify() {
    return text();
}

std::string Variable::text() {
    return std::string{symbol};
}

CAS_NAMESPACE_END