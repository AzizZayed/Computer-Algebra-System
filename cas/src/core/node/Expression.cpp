//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "core/node/Expression.h"
#include "core/node/Abs.h"
#include "core/node/Negate.h"
#include "core/node/Power.h"
#include "core/node/Product.h"
#include "core/node/Sqrt.h"
#include "core/node/Sum.h"
#include "core/node/trig/ArcCos.h"
#include "core/node/trig/ArcCot.h"
#include "core/node/trig/ArcCsc.h"
#include "core/node/trig/ArcSec.h"
#include "core/node/trig/ArcSin.h"
#include "core/node/trig/ArcTan.h"
#include "core/node/trig/Cos.h"
#include "core/node/trig/Cot.h"
#include "core/node/trig/Csc.h"
#include "core/node/trig/Sec.h"
#include "core/node/trig/Sin.h"
#include "core/node/trig/Tan.h"

CAS_NAMESPACE

Expression::Expression(const ExpressionProperties& properties)
    : properties{properties} {}

Expression::~Expression() {
#if DEBUG_CAS
    printf("Destroy cas::Expression");
#endif
}

double Expression::evaluate(const std::unordered_map<char, double>& variables) {
    throw std::runtime_error("Expression::evaluate() is not implemented for " + properties.getName());
}

bool Expression::equals(Expression* expression) {
    throw std::runtime_error("Expression::equals() is not implemented for " + properties.getName());
}

Expression* Expression::clone() {
    throw std::runtime_error("Expression::clone() is not implemented for " + properties.getName());
}

Expression* Expression::derivative(char var) {
    throw std::runtime_error("Expression::derivative() is not implemented for " + properties.getName());
}

Expression* Expression::simplified() {
    throw std::runtime_error("Expression::simplified() is not implemented for " + properties.getName());
}

Expression* Expression::multiply(Expression* expression) {
    return new Product({this, expression});
}

Expression* Expression::add(Expression* expression) {
    return new Sum({this, expression});
}

Expression* Expression::subtract(Expression* expression) {
    return new Sum({this, new Negate(expression)});
}

Expression* Expression::negate() {
    return new Negate(this);
}

Expression* Expression::power(Expression* expression) {
    return new Power(this, expression);
}

Expression* Expression::power(double exponent) {
    return new Power(this, exponent);
}

Expression* Expression::sqrt() {
    return new Sqrt(this);
}

Expression* Expression::abs() {
    return new Abs(this);
}

Expression* Expression::cos() {
    return new Cos(this);
}
Expression* Expression::sin() {
    return new Sin(this);
}
Expression* Expression::tan() {
    return new Tan(this);
}
Expression* Expression::atan() {
    return new ArcTan(this);
}
Expression* Expression::acos() {
    return new ArcCos(this);
}
Expression* Expression::asin() {
    return new ArcSin(this);
}
Expression* Expression::csc() {
    return new Csc(this);
}
Expression* Expression::sec() {
    return new Sec(this);
}
Expression* Expression::cot() {
    return new Cot(this);
}
Expression* Expression::acsc() {
    return new ArcCsc(this);
}
Expression* Expression::asec() {
    return new ArcSec(this);
}
Expression* Expression::acot() {
    return new ArcCot(this);
}

double Expression::evaluate() {
    return evaluate({});
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
    return properties.getType() == expression->getProperties().getType();
}

std::string Expression::explicitText() {
    return properties.getShortName() + "(" + text() + ")";
}

CAS_NAMESPACE_END
