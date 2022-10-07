//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "cas/node/Divide.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/Sum.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Divide::Divide(Expression* dividend, Expression* divisor)
    : Expression({ExpressionType::DIVIDE, "divide", "div"}), dividend(dividend), divisor(divisor) {
    this->dividend->setParent(this);
    this->divisor->setParent(this);
}

Divide::~Divide() {
    delete dividend;
    delete divisor;

    dividend = nullptr;
    divisor = nullptr;
}

double Divide::evaluate(const VarMap& variables) {
    return dividend->evaluate(variables) / divisor->evaluate(variables);
}

bool Divide::_equals(Expression* expression) {
    auto* divide = dynamic_cast<Divide*>(expression);
    return dividend->equals(divide->dividend) && divisor->equals(divide->divisor);
}

Divide* Divide::clone() {
    return new Divide(dividend->clone(), divisor->clone());
}

Divide* Divide::_derivative(char var) {
    return new Divide(// quotient rule
            new Sum({
                    // f'g - fg'
                    new Product({
                            // f'g
                            dividend->derivative(var),// f'g
                            divisor->clone()          // g
                    }),                               // end f'*g
                    new Negate(new Product({
                            // -fg'
                            dividend->clone(),      // f
                            divisor->derivative(var)// g'
                    }))                             // end -fg'
            }),                                     // end f'g - fg'
            new Power(                              // g^2
                    divisor->clone(),               // g
                    new Const(2)                    // 2
                    )                               // end g^2
    );                                              // end quotient rule
}

Expression* Divide::simplified() {
    Expression* dividendSimplified = dividend->simplified();
    Expression* divisorSimplified = divisor->simplified();

    // TODO simplify

    return new Divide(dividendSimplified, divisorSimplified);
}

std::string Divide::latex() {
    if (dividend->isOfType(ExpressionType::CONSTANT) && divisor->isOfType(ExpressionType::CONSTANT))
        return fmt::sprintf("\\,^{%s}/_{%s}", dividend->latex(), divisor->latex());
    return fmt::sprintf("\\frac{%s}{%s}", dividend->latex(), divisor->latex());
}

std::wstring Divide::stringify() {
    return fmt::format(L"({}/{})", dividend->stringify(), divisor->stringify());
}

std::string Divide::text() {
    return fmt::format("(({})/({}))", dividend->text(), divisor->text());
}

std::string Divide::explicitText() {
    return fmt::format("div({}, {})", dividend->explicitText(), divisor->explicitText());
}

CAS_NAMESPACE_END