//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "cas/node/Power.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Ln.h"
#include "cas/node/Product.h"
#include "cas/node/Sum.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Power::Power(const ExpressionProperties& props, Expression* base, Expression* exponent)
    : Expression(props), base(base), exponent(exponent) {
    this->base->setParent(this);
    this->exponent->setParent(this);
}

Power::Power(Expression* base, Expression* exponent)
    : Power({ExpressionType::POWER, "power", "pow"}, base, exponent) {}

Power::Power(Expression* base, double exponent)
    : Power({ExpressionType::POWER, "power", "pow"}, base, new Const(exponent)) {}

Power::~Power() {
    delete base;
    delete exponent;

    base = nullptr;
    exponent = nullptr;
}

double Power::evaluate(const VariableMap& variables) {
    return pow(base->evaluate(variables), exponent->evaluate(variables));
}

bool Power::_equals(Expression* expression) {
    auto* power = dynamic_cast<Power*>(expression);
    return base->equals(power->base) && exponent->equals(power->exponent);
}

Power* Power::clone() {
    return new Power(base->clone(), exponent->clone());
}

Expression* Power::_derivative(char var) {
    bool baseIsNumber = base->isOfType(ExpressionType::CONSTANT);
    bool exponentIsNumber = exponent->isOfType(ExpressionType::CONSTANT);

    if (baseIsNumber && exponentIsNumber)// case b^k, where b and k are both numbers (constants)
        return new Const(0);

    if (!baseIsNumber && exponentIsNumber)// case [ f(x) ]^k, where k is a constant
    {
        auto* k = dynamic_cast<Const*>(exponent);

        return new Product({
                // k*f^(k-1)*f'
                exponent->clone(),                  // k
                base->derivative(var),              // f'
                new Power(                          // f^(k - 1)
                        base->clone(),              // f
                        new Const(k->getValue() - 1)// k - 1
                        )                           // end f^(k - 1)
        });                                         // end k*f^(k-1)*f'
    }

    if (baseIsNumber)// case k^[ f(x) ], where k is a constant
    {
        return new Product({
                // k^f * lnk * f'
                this->clone(),            // a^f
                exponent->derivative(var),// f'
                new Ln(base)              // lnk
        });                               // end k^f * lnk * f'
    }

    // otherwise: case [ f(x) ]^[ g(x) ], here we use the generalized power rule
    return new Product({
            // [f(x)]^[g(x)] * ( g'*lnf + g*f'/f )
            this->clone(),// [f(x)] ^ [g(x)]
            new Sum({
                    // g'*lnf + g*f'/f
                    new Product({
                            // g' * lnf
                            exponent->derivative(var),// g'
                            new Ln(base)              // lnf
                    }),                               // end g' * lnf
                    new Product({
                            // g * f' * 1/f
                            exponent->clone(),            // g
                            new Divide(                   // f'/f
                                    base->derivative(var),// f'
                                    base->clone()         // f
                                    )                     // end f'/f
                    })                                    // end g*f'/f
            })                                            // end g'*lnf + g*f'/f
    });                                                   // end [f(x)]^[g(x)] * ( g'*lnf + g*f'/f)
}

Expression* Power::simplified() {
    if (exponent->isOfType(ExpressionType::CONSTANT)) {
        double exponentValue = exponent->evaluate();
        if (exponentValue == 0) {
            return Const::one();
        }
        if (exponentValue == 1) {
            return base->simplified();
        }

        if (base->isOfType(ExpressionType::CONSTANT)) {
            if (isWholeNumber(base->evaluate()) && isWholeNumber(exponent->evaluate())) {
                double value = Expression::evaluate();
                if (value < 10000.)
                    return Const::n(value);
            }
        }
    }
    if (base->isOfType(ExpressionType::DIVIDE)) {
        auto* frac = dynamic_cast<Divide*>(base);
        return frac->getDividend()->simplified()->power(exponent->simplified())->divide(frac->getDivisor()->simplified()->power(exponent->simplified()));
    }
    if (base->isOfType(ExpressionType::POWER)) {
        auto* pow = dynamic_cast<Power*>(base);
        return pow->getBase()->simplified()->power(pow->getExponent()->simplified()->multiply(exponent->simplified()));
    }
    if (base->isOfType(ExpressionType::PRODUCT)) {
        auto* prod = dynamic_cast<Product*>(base);

        std::vector<Expression*> newFactors;
        newFactors.reserve(prod->getExpressionsSize());
        for (auto* factor: prod->getExpressions()) {
            newFactors.push_back(factor->simplified()
                                         ->power(exponent->simplified()));
        }

        return new Product(newFactors);
    }
    if (instanceof <Log>(base)) {
        auto* log = dynamic_cast<Log*>(base);
        if (log->getBase()->equals(base)) {
            return log->getArgument()->simplified();
        }
    }

    return base->simplified()->power(exponent->simplified());
}

bool Power::baseNeedsParentheses() {
    return !(base->isOfType(ExpressionType::CONSTANT) || base->isOfType(ExpressionType::VARIABLE));
}

bool Power::exponentNeedsParentheses() {
    return exponent->isOfType(ExpressionType::DIVIDE) || exponent->isOfType(ExpressionType::POWER) || instanceof <Operator>(exponent);
}

std::string Power::latex() {
    if (baseNeedsParentheses())
        return fmt::sprintf("\\left(%s\\right)^{%s}", base->latex(), exponent->latex());
    return fmt::sprintf("%s^{%s}", base->latex(), exponent->latex());
}

std::wstring Power::stringify() {
    if (baseNeedsParentheses()) {
        if (exponentNeedsParentheses())
            return fmt::format(L"({})^({})", base->stringify(), exponent->stringify());
        else
            return fmt::format(L"({})^{}", base->stringify(), exponent->stringify());
    } else {
        if (exponentNeedsParentheses())
            return fmt::format(L"{}^({})", base->stringify(), exponent->stringify());
        else
            return fmt::format(L"{}^{}", base->stringify(), exponent->stringify());
    }
}

std::string Power::text() {
    return fmt::format("({})^({})", base->text(), exponent->text());
}

std::string Power::explicitText() {
    return fmt::format("pow({}, {})", base->explicitText(), exponent->explicitText());
}

CAS_NAMESPACE_END
