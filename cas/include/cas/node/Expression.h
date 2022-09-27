//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_EXPRESSION_H
#define CAS_EXPRESSION_H

#include "IMath.h"
#include "IRepresentableMath.h"
#include "cas/CAS.h"
#include "cas/data/ExpressionProperties.h"
#include "cas/data/ExpressionType.h"
#include <cstdlib>
#include <iostream>

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
class Mod;

CAS_NAMESPACE_END

CAS_NAMESPACE

class Expression : public IMath, public IRepresentableMath {
public:
    explicit Expression(const ExpressionProperties& properties);

    virtual ~Expression();

    Expression(const Expression& expression) = delete;

    double evaluate(const VarMap& variables) override;
    virtual double evaluate();

    virtual bool equals(Expression* expression);
    virtual bool _equals(Expression* expression);

    virtual Expression* clone();

    Expression* derivative(char var) override;
    virtual Expression* _derivative(char var);

    Expression* simplified() override;
    bool isEquivalent(IMath* expression) override;

    Product* multiply(Expression* expression);
    Product* multiply(double value);
    Sum* add(Expression* expression);
    Sum* subtract(Expression* expression);
    Sum* add(double value);
    Sum* subtract(double value);
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
    Mod* mod(Expression* expression);

    ExpressionProperties getProperties() const;

    Expression* getParent() const;

    void setParent(Expression* newParent);

    bool isNegated() const;

    bool isOfType(ExpressionType type) const;

    bool isOfSameType(Expression* expression) const;

    // TODO overload operators + - * / ^

    std::string explicitText() override;

protected:
    const ExpressionProperties properties;
    Expression* parent = nullptr;
};

CAS_NAMESPACE_END

#endif//CAS_EXPRESSION_H
