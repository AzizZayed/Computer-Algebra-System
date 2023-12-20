//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#include "cas/node/Const.h"
#include <fmt/core.h>

CAS_NAMESPACE

const char* Const::PI_UNICODE = "\u03C0";
const char* Const::E_UNICODE = "e";
const char* Const::PHI_UNICODE = "\u03D5";

const char* Const::PI_LATEX = "\\pi ";
const char* Const::E_LATEX = "e";
const char* Const::PHI_LATEX = "\\varphi ";

Const::Const(double value)
    : Expression {{ExpressionType::CONSTANT, "constant", "const"}}, value {value} {}

Const* Const::clone() {
    return Const::n(value);
}

double Const::evaluate(const VariableMap&) {
    return value;
}

bool Const::_equals(Expression* expression) {
    return doubleEquals(value, expression->evaluate());
}

bool Const::is(double val, double eps = 1e-6) const {
    return doubleEquals(this->value, val, eps);
}

bool Const::isSymbol() const {
    return is(math_constants::PI) || is(math_constants::E) || is(math_constants::PHI);
}

Const* Const::_derivative(char) {
    return Const::zero();
}

Const* Const::simplified() {
    return clone();
}

std::string Const::latex() {
    if (is(math_constants::PI)) {
        return PI_LATEX;
    }
    if (is(math_constants::E)) {
        return E_LATEX;
    }
    if (is(math_constants::PHI)) {
        return PHI_LATEX;
    }

    return text();
}

std::string Const::str() {
    if (is(math_constants::PI)) {
        return PI_UNICODE;
    }
    if (is(math_constants::E)) {
        return E_UNICODE;
    }
    if (is(math_constants::PHI)) {
        return PHI_UNICODE;
    }

    return text();
}

std::string Const::text() {
    double intPart;
    if (std::modf(value, &intPart) == 0.0) {
        return fmt::format("{:.0f}", value);
    }

    return std::to_string(value);
}

CAS_NAMESPACE_END
