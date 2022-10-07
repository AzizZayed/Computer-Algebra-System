//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#include "cas/node/Const.h"
#include "cas/util/StringUtils.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

const wchar_t* Const::PI_UNICODE = L"\u03C0";
const wchar_t* Const::E_UNICODE = L"e";
const wchar_t* Const::PHI_UNICODE = L"\u03D5";

const char* Const::PI_LATEX = "\\pi";
const char* Const::E_LATEX = "e";
const char* Const::PHI_LATEX = "\\varphi";

Const::Const(double value)
    : Expression{{ExpressionType::CONSTANT, "constant", "const"}}, value{value} {}

Const* Const::clone() {
    return new Const{value};
}

double Const::evaluate(const VarMap&) {
    return value;
}

bool Const::_equals(Expression* expression) {
    auto* constant = dynamic_cast<Const*>(expression);
    return floatingsEqual(value, constant->value);
}

Const* Const::_derivative(char) {
    return new Const{0.0};
}

Const* Const::simplified() {
    return clone();
}

std::string Const::latex() {
    if (value == math::PI) {
        return PI_LATEX;
    }
    if (value == math::E) {
        return E_LATEX;
    }
    if (value == math::PHI) {
        return PHI_LATEX;
    }

    return text();
}

std::wstring Const::stringify() {
    if (value == math::PI) {
        return PI_UNICODE;
    }
    if (value == math::E) {
        return E_UNICODE;
    }
    if (value == math::PHI) {
        return PHI_UNICODE;
    }

    return fmt::to_wstring(value);
}

std::string Const::text() {
    if (value == std::floor(value)) {
        return std::to_string(int64_t(value));
    }

    return std::to_string(value);
}

CAS_NAMESPACE_END
