//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "cas/node/Var.h"
#include "cas/node/Const.h"

CAS_NAMESPACE

Var::Var(char variable)
    : Expression({ExpressionType::VARIABLE, "variable", "var"}), symbol(variable) {}

Var* Var::clone() {
    return new Var(symbol);
}

double Var::evaluate(const VariableMap& variables) {
    if (!variables.contains(symbol))
        throw std::runtime_error("Var not found for evaluation");
    return variables.at(symbol);
}

bool Var::_equals(Expression* expression) {
    auto* var = dynamic_cast<Var*>(expression);
    return var->getSymbol() == symbol;
}

Expression* Var::_derivative(char var) {
    double derivative = symbol == var ? 1.0 : 0.0;
    return new Const{derivative};
}

Var* Var::simplified() {
    return clone();
}

std::string Var::latex() {
    return text();
}

std::string Var::str() {
    return text();
}

std::string Var::text() {
    return std::string{symbol};
}

CAS_NAMESPACE_END