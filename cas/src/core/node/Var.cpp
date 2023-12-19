//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "cas/node/Var.h"
#include "cas/data/VariableMap.h"
#include "cas/node/Const.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

Var::Var(char variable)
    : Expr({ExpressionType::VARIABLE, "variable", "var"}), symbol(variable) {}

ExprPtr Var::clone() {
    return Var::from(symbol);
}

double Var::evaluate(const VariableMap& variables) {
    if (!variables.contains(symbol))
        throw std::runtime_error("Var not found for evaluation");
    return variables.at(symbol);
}

bool Var::_equals(const ExprPtr& expression) {
    auto* var = dynamic_cast<Var*>(expression.get());
    return var->getSymbol() == symbol;
}

ExprPtr Var::_derivative(char var) {
    double derivative = symbol == var ? 1.0 : 0.0;
    return Const::n(derivative);
}

ExprPtr Var::simplified() {
    return clone();
}

std::string Var::latex() {
    return text();
}

std::wstring Var::stringify() {
    return toWstring(text());
}

std::string Var::text() {
    return std::string{symbol};
}

CAS_NAMESPACE_END