//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "core/CAS.h"
#include "core/node/Power.h"

CAS_NAMESPACE

Power::Power(Expression* base, Expression* exponent)
: Expression({ExpressionType::POWER, "power", "pow"}), base(base), exponent(exponent)
{
    this->base->setParent(this);
    this->exponent->setParent(this);
}

Power::~Power()
{
#if CAS_DEBUG
    printf("Destroy Power\n");
#endif

    delete base;
    delete exponent;
}

double Power::evaluate(const std::unordered_map<char, double>& variables) {
    return pow(base->evaluate(variables), exponent->evaluate(variables));
}

bool Power::equals(Expression* expression) {
    if (expression->getProperties().getType() == ExpressionType::POWER) {
        auto* power = dynamic_cast<Power*>(expression);
        return base->equals(power->base) && exponent->equals(power->exponent);
    }

    return false;
}

Power* Power::clone() {
    return new Power(base->clone(), exponent->clone());
}

Expression * Power::derivative(char var) {
    return nullptr; // TODO implement
}

Expression* Power::simplified() {
    return nullptr; // TODO implement simplified
}

std::string Power::latex() {
    return "";
}

std::string Power::stringify() {
    return "";
}

std::string Power::text() {
    return "";
}

std::string Power::explicitText() {
    return "";
}

CAS_NAMESPACE_END

