//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_EXPRESSION_H
#define CAS_EXPRESSION_H

#include "IMath.h"
#include "IRepresentableMath.h"
#include "cas/data/ExpressionProperties.h"
#include "cas/data/ExpressionType.h"

CAS_NAMESPACE

class Const;
class Var;

class Prod;
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

class Min;
class Max;

class Expr;

using ExprPtr = std::shared_ptr<Expr>;
using ConstPtr = std::shared_ptr<Const>;
using VarPtr = std::shared_ptr<Var>;
using ProdPtr = std::shared_ptr<Prod>;
using SumPtr = std::shared_ptr<Sum>;
using DividePtr = std::shared_ptr<Divide>;
using NegatePtr = std::shared_ptr<Negate>;
using PowerPtr = std::shared_ptr<Power>;
using ExpPtr = std::shared_ptr<Exp>;
using LogPtr = std::shared_ptr<Log>;
using LnPtr = std::shared_ptr<Ln>;
using RootPtr = std::shared_ptr<Root>;
using SqrtPtr = std::shared_ptr<Sqrt>;
using CbrtPtr = std::shared_ptr<Cbrt>;
using SinPtr = std::shared_ptr<Sin>;
using CosPtr = std::shared_ptr<Cos>;
using TanPtr = std::shared_ptr<Tan>;
using CotPtr = std::shared_ptr<Cot>;
using CscPtr = std::shared_ptr<Csc>;
using SecPtr = std::shared_ptr<Sec>;
using ArcSinPtr = std::shared_ptr<ArcSin>;
using ArcCosPtr = std::shared_ptr<ArcCos>;
using ArcTanPtr = std::shared_ptr<ArcTan>;
using ArcCotPtr = std::shared_ptr<ArcCot>;
using ArcCscPtr = std::shared_ptr<ArcCsc>;
using ArcSecPtr = std::shared_ptr<ArcSec>;
using AbsPtr = std::shared_ptr<Abs>;
using FloorPtr = std::shared_ptr<Floor>;
using CeilPtr = std::shared_ptr<Ceil>;
using RoundPtr = std::shared_ptr<Round>;
using SignPtr = std::shared_ptr<Sign>;
using ModPtr = std::shared_ptr<Mod>;
using MinPtr = std::shared_ptr<Min>;
using MaxPtr = std::shared_ptr<Max>;

class Expr : public IMath<ExprPtr>, public IRepresentableMath, public std::enable_shared_from_this<Expr> {
public:
    explicit Expr(const ExpressionProperties& properties);

    virtual ~Expr() = default;

    Expr(const Expr& expression) = delete;

    double evaluate(const VariableMap& variables) override;
    virtual double evaluate();

    virtual bool equals(ExprPtr expression);
    virtual bool _equals(ExprPtr expression);

    virtual ExprPtr clone();

    ExprPtr derivative(char var) override;
    virtual ExprPtr _derivative(char var);

    ExprPtr simplified() override;
    bool isEquivalent(ExprPtr expression) override;

    ProdPtr multiply(ExprPtr expression);
    ProdPtr multiply(double value);
    SumPtr add(ExprPtr expression);
    SumPtr subtract(ExprPtr expression);
    SumPtr add(double value);
    SumPtr subtract(double value);
    DividePtr divide(ExprPtr expression);
    DividePtr divide(double divisor);
    NegatePtr negate();

    PowerPtr power(ExprPtr expression);
    PowerPtr power(double exponent);
    ExpPtr exp();
    LogPtr log(ExprPtr base);
    LogPtr log(double base);
    LnPtr ln();

    RootPtr root(ExprPtr root);
    RootPtr root(double root);
    SqrtPtr sqrt();
    CbrtPtr cbrt();

    CosPtr cos();
    SinPtr sin();
    TanPtr tan();
    ArcTanPtr atan();
    ArcCosPtr acos();
    ArcSinPtr asin();
    CscPtr csc();
    SecPtr sec();
    CotPtr cot();
    ArcCscPtr acsc();
    ArcSecPtr asec();
    ArcCotPtr acot();

    AbsPtr abs();
    FloorPtr floor();
    CeilPtr ceil();
    RoundPtr round();
    SignPtr sign();
    ModPtr mod(ExprPtr expression);

    ExprPtr reciprocal();

    bool operator<(const Expr& expression) const;

    bool lessThan(ExprPtr expression) const;

    static bool compare(ExprPtr left, ExprPtr right);

    ExpressionProperties getProperties() const;

    Expr* getParent() const;

    void setParent(Expr* newParent);

    bool isNegated() const;

    bool isOfType(ExpressionType type) const;

    bool isOfSameType(ExprPtr expression) const;

    // TODO overload math operators + - * / ^

    std::string explicitText() override;

protected:
    const ExpressionProperties properties;
    Expr* parent = nullptr;
};

CAS_NAMESPACE_END

#endif//CAS_EXPRESSION_H
