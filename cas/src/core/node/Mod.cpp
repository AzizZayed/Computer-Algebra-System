//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Mod.h"
#include "cas/node/Const.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

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
    delete dividend;
    delete divisor;

    dividend = nullptr;
    divisor = nullptr;
}

double Mod::evaluate(const VarMap& variables) {
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
        if (isWholeNumber(dividend->evaluate()) && isWholeNumber(divisor->evaluate())) {
            return new Const(Expression::evaluate());
        }
    }
    if (dividend->isOfType(ExpressionType::CONSTANT) && dividend->evaluate() == 0) {
        return Const::zero();
    }

    return new Mod(dividend->simplified(), divisor->simplified());
}

std::string Mod::latex() {
    return fmt::format(R"(\mod{\left({},{}\right)})", dividend->latex(), divisor->latex());
}

std::wstring Mod::stringify() {
    return fmt::format(L"mod({}, {})", dividend->stringify(), divisor->stringify());
}

std::string Mod::text() {
    return fmt::format("mod({}, {})", dividend->text(), divisor->text());
}

std::string Mod::explicitText() {
    return fmt::format("mod({}, {})", dividend->explicitText(), divisor->explicitText());
}

CAS_NAMESPACE_END