//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/Mod.h"
#include "cas/node/Const.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Mod::Mod(const ExprPtr& dividend, const ExprPtr& divisor)
    : Expr({ExpressionType::MODULO, "modulo", "mod"}), dividend(dividend), divisor(divisor) {

    if (divisor->isOfType(ExpressionType::CONSTANT) && divisor->evaluate() == 0) {
        throw std::invalid_argument("Divisor cannot be zero");
    }

    this->dividend->setParent(this);
    this->divisor->setParent(this);
}

double Mod::evaluate(const VariableMap& variables) {
    return std::fmod(dividend->evaluate(variables), divisor->evaluate(variables));
}

bool Mod::_equals(const ExprPtr& expression) {
    if (this == expression.get())
        return true;

    if (expression->isOfType(ExpressionType::MODULO)) {
        auto* mod = dynamic_cast<Mod*>(expression.get());
        return dividend->equals(mod->dividend) && divisor->equals(mod->divisor);
    }

    return false;
}

ExprPtr Mod::clone() {
    return Mod::from(dividend->clone(), divisor->clone());
}

ExprPtr Mod::simplified() {
    if (dividend->isOfType(ExpressionType::CONSTANT) && divisor->isOfType(ExpressionType::CONSTANT)) {
        if (isWholeNumber(dividend->evaluate()) && isWholeNumber(divisor->evaluate())) {
            return Const::n(Expr::evaluate());
        }
    }
    if (dividend->isOfType(ExpressionType::CONSTANT) && dividend->evaluate() == 0) {
        return Const::zero();
    }

    return Mod::from(dividend->simplified(), divisor->simplified());
}

std::string Mod::latex() {
    return fmt::sprintf(R"(\mod{\left(%s,%s\right)})", dividend->latex(), divisor->latex());
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
