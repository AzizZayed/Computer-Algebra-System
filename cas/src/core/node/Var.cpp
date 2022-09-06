//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "core/node/Var.h"
#include "core/CAS.h"

CAS_NAMESPACE

Var::Var(char variable)
    : symbol(variable), Expression({ExpressionType::VARIABLE, "variable", "var"}) {
#if DEBUG_CAS
    printf("%s(%c)\n", properties.getName().c_str(), variable);
#endif
}

Var::~Var() {
#if DEBUG_CAS
    printf("Destroy cas::Var\n");
#endif
}

Var* Var::clone() {
    return new Var(symbol);
}

double Var::evaluate(const std::unordered_map<char, double>& variables) {
    if (variables.find(symbol) == variables.end())
        throw std::runtime_error("Var not found for evaluation");
    return variables.at(symbol);
}

bool Var::equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->getProperties().getType() == ExpressionType::VARIABLE) {
        auto* var = dynamic_cast<Var*>(expression);
        return var->getSymbol() == symbol;
    }
    return false;
}

Const* Var::derivative(char var) {
    double derivative = symbol == var ? 1.0 : 0.0;
    return new Const{derivative};
}

Var* Var::simplified() {
    return clone();
}

std::string Var::latex() {
    return text();
}

std::string Var::stringify() {
    return text();
}

std::string Var::text() {
    return std::string{symbol};
}

CAS_NAMESPACE_END