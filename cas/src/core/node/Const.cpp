//
// Created by Abd-El-Aziz Zayed on 2022-08-26.
//

#include "core/node/Const.h"

CAS_NAMESPACE

const std::string Const::PI_UNICODE = "\u03C0";
const std::string Const::E_UNICODE = "e";
const std::string Const::PHI_UNICODE = "\u03D5";

const std::string Const::PI_LATEX = "\\pi";
const std::string Const::E_LATEX = "e";
const std::string Const::PHI_LATEX = "\\varphi";

Const::Const(double value)
    : value{value}, Expression{{ExpressionType::CONSTANT, "constant", "const"}} {
#if DEBUG_CAS
    std::string str = properties.getName();
    printf("%s(%f)\n", str.c_str(), value);
#endif
}

Const::~Const() {
#if DEBUG_CAS
    printf("Destroy cas::Const\n");
#endif
}

Const* Const::clone() {
    return new Const{value};
}

double Const::evaluate(const std::unordered_map<char, double>& variables) {
    return value;
}

bool Const::equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->getProperties().getType() == ExpressionType::CONSTANT) {
        auto* constant = dynamic_cast<Const*>(expression);
        return value == constant->getValue();
    }
    return false;
}

Const* Const::derivative(char var) {
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

std::string Const::stringify() {
    if (value == math::PI) {
        return PI_UNICODE;
    }
    if (value == math::E) {
        return E_UNICODE;
    }
    if (value == math::PHI) {
        return PHI_UNICODE;
    }

    return text();
}

std::string Const::text() {
    return std::to_string(value);
}

CAS_NAMESPACE_END
