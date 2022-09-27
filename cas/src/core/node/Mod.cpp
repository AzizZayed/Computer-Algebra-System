//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Mod.h"
#include "cas/node/Const.h"
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

Mod::Mod(Expression* dividend, Expression* divisor)
    : Expression({ExpressionType::MODULO, "modulo", "mod"}), dividend(dividend), divisor(divisor) {

    if (divisor->isOfType(ExpressionType::CONSTANT) && divisor->evaluate() == 0) {
        throw std::invalid_argument("Divisor cannot be zero");
    }

    this->dividend->setParent(this);
    this->divisor->setParent(this);
}

Mod::~Mod() {
#if DEBUG_CAS
    wPrint(L"Destroy cas::Mod\n");
#endif

    delete dividend;
    delete divisor;

    dividend = nullptr;
    divisor = nullptr;
}

double Mod::evaluate(const std::unordered_map<char, double>& variables) {
    return std::fmod(dividend->evaluate(variables), divisor->evaluate(variables));
}

bool Mod::_equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->isOfType(ExpressionType::MODULO)) {
        auto* mod = dynamic_cast<Mod*>(expression);
        return dividend->equals(mod->dividend) && divisor->equals(mod->divisor);
    }

    return false;
}

Mod* Mod::clone() {
    return new Mod(dividend->clone(), divisor->clone());
}

Expression* Mod::simplified() {
    if (dividend->isOfType(ExpressionType::CONSTANT) && divisor->isOfType(ExpressionType::CONSTANT)) {
        return new Const(Expression::evaluate());
    }
    return new Mod(dividend->simplified(), divisor->simplified());// TODO: simplify
}

std::string Mod::latex() {
    return "\\operatorname{mod}\\left(" + dividend->latex() + ", " + divisor->latex() + "\\right)";
}

std::wstring Mod::stringify() {
    return toWstring(properties.getShortName()) + L"(" + dividend->stringify() + L", " + divisor->stringify() + L")";
}

std::string Mod::text() {
    return properties.getShortName() + "(" + dividend->text() + ", " + divisor->text() + ")";
}

std::string Mod::explicitText() {
    return properties.getName() + "(" + dividend->explicitText() + ", " + divisor->explicitText() + ")";
}

CAS_NAMESPACE_END