//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_EXPRESSION_H
#define CAS_EXPRESSION_H

#include "ExpressionProperties.h"
#include "ExpressionType.h"
#include "IMathNode.h"
#include "cas/CAS.h"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

CAS_NAMESPACE

class Product;
class Sum;
class Divide;
class Negate;

class Power;
class Exp;
class Log;
class Ln;

class Root;
class Sqrt;
class Cbrt;

class Sin;
class Cos;
class Tan;
class Cot;
class Csc;
class Sec;
class ArcSin;
class ArcCos;
class ArcTan;
class ArcCot;
class ArcCsc;
class ArcSec;

class Abs;
class Floor;
class Ceil;
class Round;
class Sign;

CAS_NAMESPACE_END

CAS_NAMESPACE

class Expression : public IMathNode {
public:
    explicit Expression(const ExpressionProperties& properties);

    virtual ~Expression();

    Expression(const Expression& expression) = delete;

    virtual double evaluate(const std::unordered_map<char, double>& variables);
    double evaluate();

    virtual bool equals(Expression* expression);

    virtual Expression* clone();

    virtual Expression* derivative(char var);

    virtual Expression* simplified();

    Product* multiply(Expression* expression);
    Sum* add(Expression* expression);
    Sum* subtract(Expression* expression);
    Divide* divide(Expression* expression);
    Negate* negate();

    Power* power(Expression* expression);
    Power* power(double exponent);
    Exp* exp();
    Log* log(Expression* base);
    Log* log(double base);
    Ln* ln();

    Root* root(Expression* root);
    Root* root(double root);
    Sqrt* sqrt();
    Cbrt* cbrt();

    Cos* cos();
    Sin* sin();
    Tan* tan();
    ArcTan* atan();
    ArcCos* acos();
    ArcSin* asin();
    Csc* csc();
    Sec* sec();
    Cot* cot();
    ArcCsc* acsc();
    ArcSec* asec();
    ArcCot* acot();

    Abs* abs();
    Floor* floor();
    Ceil* ceil();
    Round* round();
    Sign* sign();

    ExpressionProperties getProperties() const;

    Expression* getParent() const;

    void setParent(Expression* newParent);

    bool isNegated() const;

    bool isOfType(ExpressionType type) const;

    bool isOfSameType(Expression* expression) const;

    std::string explicitText() override;

protected:
    const ExpressionProperties properties;
    Expression* parent = nullptr;
};

CAS_NAMESPACE_END

#endif//CAS_EXPRESSION_H
