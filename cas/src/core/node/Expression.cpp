//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "cas/node/Expression.h"
#include "cas/node/Abs.h"
#include "cas/node/Cbrt.h"
#include "cas/node/Ceil.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Exp.h"
#include "cas/node/Floor.h"
#include "cas/node/Ln.h"
#include "cas/node/Mod.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
#include "cas/node/Round.h"
#include "cas/node/Sign.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "cas/node/trig/ArcCos.h"
#include "cas/node/trig/ArcCot.h"
#include "cas/node/trig/ArcCsc.h"
#include "cas/node/trig/ArcSec.h"
#include "cas/node/trig/ArcSin.h"
#include "cas/node/trig/ArcTan.h"
#include "cas/node/trig/Cos.h"
#include "cas/node/trig/Cot.h"
#include "cas/node/trig/Csc.h"
#include "cas/node/trig/Sec.h"
#include "cas/node/trig/Sin.h"
#include "cas/node/trig/Tan.h"
#include <fmt/core.h>
#include <stdexcept>

CAS_NAMESPACE

Expression::Expression(const ExpressionProperties& properties)
    : properties{properties} {}

double Expression::evaluate(const VariableMap&) {
    throw std::runtime_error("Expression::evaluate() is not implemented for " + properties.getName());
}

double Expression::evaluate() {
    return evaluate({});
}

bool Expression::equals(Expression* expression) {
    if (this == expression)
        return true;

    if (!isOfType(expression->getProperties().getType()))
        return false;

    return _equals(expression);
}

bool Expression::_equals(Expression*) {
    throw std::runtime_error("Expression::equals() is not implemented for " + properties.getName());
}

Expression* Expression::clone() {
    throw std::runtime_error("Expression::clone() is not implemented for " + properties.getName());
}

Expression* Expression::derivative(char var) {
    return _derivative(var);
}

Expression* Expression::_derivative(char) {
    throw std::runtime_error("Expression::derivative() is not implemented for " + properties.getName());
}

Expression* Expression::simplified() {
    throw std::runtime_error("Expression::simplified() is not implemented for " + properties.getName());
}

bool Expression::isEquivalent(cas::IMath*) {
    throw std::runtime_error("Expression::isEquivalent() is not implemented for " + properties.getName());
}

Product* Expression::multiply(Expression* expression) {
    return new Product({this, expression});
}

Product* Expression::multiply(double value) {
    return new Product({this, Const::n(value)});
}

Sum* Expression::add(Expression* expression) {
    return new Sum({this, expression});
}

Sum* Expression::add(double value) {
    return this->add(new Const(value));
}

Sum* Expression::subtract(Expression* expression) {
    return new Sum({this, new Negate(expression)});
}

Sum* Expression::subtract(double value) {
    return this->subtract(new Const(value));
}

Divide* Expression::divide(Expression* expression) {
    return new Divide(this, expression);
}

Divide* Expression::divide(double divisor) {
    return this->divide(Const::n(divisor));
}

Negate* Expression::negate() {
    return new Negate(this);
}

Power* Expression::power(Expression* expression) {
    return new Power(this, expression);
}

Power* Expression::power(double exponent) {
    return new Power(this, exponent);
}

Exp* Expression::exp() {
    return new Exp(this);
}

Log* Expression::log(Expression* base) {
    return new Log(base, this);
}
Log* Expression::log(double base) {
    return new Log(base, this);
}

Ln* Expression::ln() {
    return new Ln(this);
}

Root* Expression::root(Expression* root) {
    return new Root(this, root);
}

Root* Expression::root(double root) {
    return new Root(this, root);
}

Sqrt* Expression::sqrt() {
    return new Sqrt(this);
}

Cbrt* Expression::cbrt() {
    return new Cbrt(this);
}

Abs* Expression::abs() {
    return new Abs(this);
}

Cos* Expression::cos() {
    return new Cos(this);
}
Sin* Expression::sin() {
    return new Sin(this);
}
Tan* Expression::tan() {
    return new Tan(this);
}
ArcTan* Expression::atan() {
    return new ArcTan(this);
}
ArcCos* Expression::acos() {
    return new ArcCos(this);
}
ArcSin* Expression::asin() {
    return new ArcSin(this);
}
Csc* Expression::csc() {
    return new Csc(this);
}
Sec* Expression::sec() {
    return new Sec(this);
}
Cot* Expression::cot() {
    return new Cot(this);
}
ArcCsc* Expression::acsc() {
    return new ArcCsc(this);
}
ArcSec* Expression::asec() {
    return new ArcSec(this);
}
ArcCot* Expression::acot() {
    return new ArcCot(this);
}

Floor* Expression::floor() {
    return new Floor(this);
}

Ceil* Expression::ceil() {
    return new Ceil(this);
}

Round* Expression::round() {
    return new Round(this);
}

Sign* Expression::sign() {
    return new Sign(this);
}

Mod* Expression::mod(Expression* expression) {
    return new Mod(this, expression);
}

Expression* Expression::reciprocal() {
    if (isOfType(ExpressionType::DIVIDE)) {
        auto* div = dynamic_cast<Divide*>(this);
        return div->getDivisor()->divide(div->getDividend());
    }

    return Const::n(1)->divide(this);
}

bool Expression::operator<(const cas::Expression& expression) const {
    ExpressionType type = properties.getType();
    ExpressionType expressionType = expression.properties.getType();

    int diff = static_cast<uint8_t>(type) - static_cast<uint8_t>(expressionType);

    if (diff == 0) {
        if (isOfType(ExpressionType::VARIABLE)) {
            auto* var = dynamic_cast<const Var*>(this);
            auto* otherVar = dynamic_cast<const Var*>(&expression);

            return var->getSymbol() < otherVar->getSymbol();
        }
        if (isOfType(ExpressionType::CONSTANT)) {
            auto* constant = dynamic_cast<const Const*>(this);
            auto* otherConstant = dynamic_cast<const Const*>(&expression);

            return constant->getValue() < otherConstant->getValue();
        }
        if (isOfType(ExpressionType::DIVIDE)) {
            auto* divide = dynamic_cast<const Divide*>(this);
            auto* otherDivide = dynamic_cast<const Divide*>(&expression);

            return divide->getDividend()->lessThan(otherDivide->getDividend()) || divide->getDivisor()->lessThan(otherDivide->getDivisor());
        }

        // TODO compare other individual types (redesign needed, use polymorphism/inheritance)
    }

    return diff < 0;
}

bool Expression::lessThan(cas::Expression* expression) const {
    return *this < *expression;
}

bool Expression::compare(cas::Expression* left, cas::Expression* right) {
    return left->lessThan(right);
}

ExpressionProperties Expression::getProperties() const {
    return properties;
}

Expression* Expression::getParent() const {
    return parent;
}

void Expression::setParent(Expression* newParent) {
    this->parent = newParent;
}

bool Expression::isNegated() const {
    return properties.getType() == ExpressionType::NEGATE;
}

bool Expression::isOfType(ExpressionType type) const {
    return properties.getType() == type;
}

bool Expression::isOfSameType(Expression* expression) const {
    return isOfType(expression->getProperties().getType());
}

std::string Expression::explicitText() {
    return properties.getShortName() + "(" + text() + ")";
}

CAS_NAMESPACE_END
