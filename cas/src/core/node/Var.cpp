//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "cas/node/Var.h"
#include "cas/CAS.h"
#include "cas/node/Const.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

Var::Var(char variable)
    : symbol(variable), Expression({ExpressionType::VARIABLE, "variable", "var"}) {
#if DEBUG_CAS
    wprintf(L"%s(%c)\n", properties.getName().c_str(), variable);
#endif
}

Var::~Var() {
#if DEBUG_CAS
    wPrint(L"Destroy cas::Var\n");
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

bool Var::_equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->getProperties().getType() == ExpressionType::VARIABLE) {
        auto* var = dynamic_cast<Var*>(expression);
        return var->getSymbol() == symbol;
    }
    return false;
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

std::wstring Var::stringify() {
    return toWstring(text());
}

std::string Var::text() {
    return std::string{symbol};
}

CAS_NAMESPACE_END