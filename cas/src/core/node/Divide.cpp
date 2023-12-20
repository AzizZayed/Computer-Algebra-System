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

double Divide::evaluate(const VariableMap& variables) {
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
    return dividend->derivative(var)
            ->multiply(divisor->clone())  // f' * g
            ->subtract(dividend->clone()
                               ->multiply(divisor->derivative(var)))  // f' * g - f * g'
            ->divide(divisor->clone()
                             ->power(2));  // (f' * g - f * g') / g^2
}

Expression* Divide::simplified() {
    if (dividend->equals(divisor)) {
        return Const::one();
    }

    bool dividendIsDivide = dividend->isOfType(ExpressionType::DIVIDE);
    bool divisorIsDivide = divisor->isOfType(ExpressionType::DIVIDE);

    if (dividendIsDivide && !divisorIsDivide) {  // (g/h)/f = g/(h*f)
        auto* dDividend = dynamic_cast<Divide*>(dividend);
        return dDividend->dividend->simplified()
                ->divide(dDividend->divisor->simplified()
                                 ->multiply(divisor));
    }
    if (!dividendIsDivide && divisorIsDivide) {  // f/(g/h) = (f*h)/g
        auto* divisorDivide = dynamic_cast<Divide*>(divisor);
        return dividend
                ->multiply(divisorDivide->divisor->simplified())
                ->divide(divisorDivide->dividend->simplified());
    }
    if (dividendIsDivide) {  // (g/h)/(f/k) = (g*k)/(h*f)
        auto* dividendDivide = dynamic_cast<Divide*>(dividend);
        auto* divisorDivide = dynamic_cast<Divide*>(divisor);
        return dividendDivide->dividend->simplified()
                ->multiply(divisorDivide->divisor->simplified())
                ->divide(dividendDivide->divisor->simplified()
                                 ->multiply(divisorDivide->dividend->simplified()));
    }

    if (dividend->isOfType(ExpressionType::CONSTANT) && divisor->isOfType(ExpressionType::CONSTANT)) {
        double dividendValue = dividend->evaluate();
        double divisorValue = divisor->evaluate();
        if (divisorValue == 0) {
            throw std::runtime_error("Division by zero");
        }

        double result = dividendValue / divisorValue;
        if (isWholeNumber(result)) {
            return new Const(result);
        }
        return Const::n(dividendValue)->divide(Const::n(divisorValue));
    }

    // TODO cancel out common factors with products

    return dividend->divide(divisor);
}

std::string Divide::latex() {
    if (dividend->isOfType(ExpressionType::CONSTANT) && divisor->isOfType(ExpressionType::CONSTANT))
        return fmt::sprintf("\\,^{%s}/_{%s}", dividend->latex(), divisor->latex());
    return fmt::sprintf("\\frac{%s}{%s}", dividend->latex(), divisor->latex());
}

std::string Divide::str() {
    return fmt::format("({}/{})", dividend->str(), divisor->str());
}

std::string Divide::text() {
    return fmt::format("(({})/({}))", dividend->text(), divisor->text());
}

std::string Divide::explicitText() {
    return fmt::format("div({}, {})", dividend->explicitText(), divisor->explicitText());
}

CAS_NAMESPACE_END