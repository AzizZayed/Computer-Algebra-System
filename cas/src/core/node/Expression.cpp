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
#include "cas/node/Prod.h"
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
#include <vector>

CAS_NAMESPACE

Expr::Expr(const ExpressionProperties& properties)
    : properties{properties} {}

double Expr::evaluate(const VariableMap&) {
    throw std::runtime_error("Expression::evaluate() is not implemented for " + properties.getName());
}

double Expr::evaluate() {
    return evaluate({});
}

bool Expr::equals(ExprPtr expression) {
    if (this == expression.get())
        return true;

    if (!isOfType(expression->getProperties().getType()))
        return false;

    return _equals(expression);
}

bool Expr::_equals(ExprPtr) {
    throw std::runtime_error("Expression::equals() is not implemented for " + properties.getName());
}

ExprPtr Expr::clone() {
    throw std::runtime_error("Expression::clone() is not implemented for " + properties.getName());
}

ExprPtr Expr::derivative(char var) {
    return _derivative(var);
}

ExprPtr Expr::_derivative(char) {
    throw std::runtime_error("Expression::derivative() is not implemented for " + properties.getName());
}

ExprPtr Expr::simplified() {
    throw std::runtime_error("Expression::simplified() is not implemented for " + properties.getName());
}

bool Expr::isEquivalent(ExprPtr) {
    throw std::runtime_error("Expression::isEquivalent() is not implemented for " + properties.getName());
}

ProdPtr Expr::multiply(ExprPtr expression) {
    return std::make_shared<Prod>(std::vector<ExprPtr>{shared_from_this(), expression});
}

ProdPtr Expr::multiply(double value) {
    return std::make_shared<Prod>(std::vector<ExprPtr>{shared_from_this(), Const::n(value)});
}

SumPtr Expr::add(ExprPtr expression) {
    return std::make_shared<Sum>(std::vector<ExprPtr>{shared_from_this(), expression});
}

SumPtr Expr::add(double value) {
    return add(Const::n(value));
}

SumPtr Expr::subtract(ExprPtr expression) {
    const NegatePtr& negate = Negate::from(expression);
    return std::make_shared<Sum>(std::vector<ExprPtr>{shared_from_this(), negate});
}

SumPtr Expr::subtract(double value) {
    return subtract(Const::n(value));
}

DividePtr Expr::divide(ExprPtr expression) {
    return std::make_shared<Divide>(shared_from_this(), expression);
}

DividePtr Expr::divide(double divisor) {
    return this->divide(Const::n(divisor));
}

NegatePtr Expr::negate() {
    return std::make_shared<Negate>(shared_from_this());
}

PowerPtr Expr::power(ExprPtr expression) {
    return std::make_shared<Power>(shared_from_this(), expression);
}

PowerPtr Expr::power(double exponent) {
    return std::make_shared<Power>(shared_from_this(), exponent);
}

ExpPtr Expr::exp() {
    return std::make_shared<Exp>(shared_from_this());
}

LogPtr Expr::log(ExprPtr base) {
    return std::make_shared<Log>(base, shared_from_this());
}
LogPtr Expr::log(double base) {
    return std::make_shared<Log>(base, shared_from_this());
}

LnPtr Expr::ln() {
    return std::make_shared<Ln>(shared_from_this());
}
RootPtr Expr::root(ExprPtr root) {
    return std::make_shared<Root>(shared_from_this(), root);
}

RootPtr Expr::root(double root) {
    return std::make_shared<Root>(shared_from_this(), root);
}

SqrtPtr Expr::sqrt() {
    return std::make_shared<Sqrt>(shared_from_this());
}

CbrtPtr Expr::cbrt() {
    return std::make_shared<Cbrt>(shared_from_this());
}

AbsPtr Expr::abs() {
    return std::make_shared<Abs>(shared_from_this());
}

CosPtr Expr::cos() {
    return std::make_shared<Cos>(shared_from_this());
}
SinPtr Expr::sin() {
    return std::make_shared<Sin>(shared_from_this());
}
TanPtr Expr::tan() {
    return std::make_shared<Tan>(shared_from_this());
}
ArcTanPtr Expr::atan() {
    return std::make_shared<ArcTan>(shared_from_this());
}
ArcCosPtr Expr::acos() {
    return std::make_shared<ArcCos>(shared_from_this());
}
ArcSinPtr Expr::asin() {
    return std::make_shared<ArcSin>(shared_from_this());
}
CscPtr Expr::csc() {
    return std::make_shared<Csc>(shared_from_this());
}
SecPtr Expr::sec() {
    return std::make_shared<Sec>(shared_from_this());
}
CotPtr Expr::cot() {
    return std::make_shared<Cot>(shared_from_this());
}
ArcCscPtr Expr::acsc() {
    return std::make_shared<ArcCsc>(shared_from_this());
}
ArcSecPtr Expr::asec() {
    return std::make_shared<ArcSec>(shared_from_this());
}
ArcCotPtr Expr::acot() {
    return std::make_shared<ArcCot>(shared_from_this());
}

FloorPtr Expr::floor() {
    return std::make_shared<Floor>(shared_from_this());
}

CeilPtr Expr::ceil() {
    return std::make_shared<Ceil>(shared_from_this());
}

RoundPtr Expr::round() {
    return std::make_shared<Round>(shared_from_this());
}

SignPtr Expr::sign() {
    return std::make_shared<Sign>(shared_from_this());
}

ModPtr Expr::mod(ExprPtr expression) {
    return std::make_shared<Mod>(shared_from_this(), expression);
}

ExprPtr Expr::reciprocal() {
    if (isOfType(ExpressionType::DIVIDE)) {
        auto* div = dynamic_cast<Divide*>(this);
        return div->getDivisor()->divide(div->getDividend());
    }

    return Const::n(1)->divide(shared_from_this());
}

bool Expr::operator<(const cas::Expr& expression) const {
    int diff = this->properties.getOrder() - expression.properties.getOrder();

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

bool Expr::lessThan(cas::ExprPtr expression) const {
    return *this < *expression;
}

bool Expr::compare(cas::ExprPtr left, cas::ExprPtr right) {
    return left->lessThan(right);
}

ExpressionProperties Expr::getProperties() const {
    return properties;
}

Expr* Expr::getParent() const {
    return parent;
}

void Expr::setParent(Expr* newParent) {
    this->parent = newParent;
}

bool Expr::isNegated() const {
    return properties.getType() == ExpressionType::NEGATE;
}

bool Expr::isOfType(ExpressionType type) const {
    return properties.getType() == type;
}

bool Expr::isOfSameType(ExprPtr expression) const {
    return isOfType(expression->getProperties().getType());
}

std::string Expr::explicitText() {
    return properties.getShortName() + "(" + text() + ")";
}

CAS_NAMESPACE_END
