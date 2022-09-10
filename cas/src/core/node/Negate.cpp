//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Negate.h"
#include "cas/node/Operator.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

Negate::Negate(Expression* expression)
    : UnaryFunction({ExpressionType::NEGATE, "negate", "neg"}, expression) {
#if DEBUG_CAS
    std::string str = properties.getName();
    wprintf(L"%s(...)\n", str.c_str());
#endif
}

Negate::~Negate() {
#if DEBUG_CAS
    wPrint(L"Destroy cas::Negate\n");
#endif
}

double Negate::evaluate(const std::unordered_map<char, double>& variables) {
    return -argument->evaluate(variables);
}

bool Negate::_equals(Expression* expr) {
    if (this == argument)
        return true;

    if (expr->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(expr);
        return this->argument->equals(negate->argument);
    }

    return false;
}

Negate* Negate::clone() {
    return new Negate(argument->clone());
}

Negate* Negate::_derivative(char var) {
    return new Negate(argument->derivative(var));
}

Expression* Negate::simplified()// TODO: Simplify
{
    auto* simplified = argument->simplified();

    if (simplified->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(simplified);
        return negate->argument->clone();
    }

    return new Negate(simplified);
}

bool Negate::needsParentheses() {
    return argument->isOfType(ExpressionType::SUM);
}

std::string Negate::latex() {
    return "-" + argument->latex();
}

std::wstring Negate::stringify() {
    if (needsParentheses())
        return L"-(" + argument->stringify() + L")";
    return L"-" + argument->stringify();
}

std::string Negate::text() {
    return "(-(" + argument->text() + "))";
}

std::string Negate::explicitText() {
    return properties.getShortName() + "(" + argument->explicitText() + ")";
}

CAS_NAMESPACE_END
