//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "cas/node/Power.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Ln.h"
#include "cas/node/Prod.h"
#include "cas/node/Sum.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Power::Power(const ExpressionProperties& props, const ExprPtr& base, const ExprPtr& exponent)
    : Expr(props), base(base), exponent(exponent) {
        this->base->setParent(this);
        this->exponent->setParent(this);
}

Power::Power(const ExprPtr& base, const ExprPtr& exponent)
    : Power({ExpressionType::POWER, "power", "pow"}, base, exponent) {}

Power::Power(const ExprPtr& base, double exponent)
    : Power({ExpressionType::POWER, "power", "pow"}, base, Const::n(exponent)) {}

double Power::evaluate(const VariableMap& variables) {
    return pow(base->evaluate(variables), exponent->evaluate(variables));
}

bool Power::_equals(const ExprPtr& expression) {
    auto* power = dynamic_cast<Power*>(expression.get());
    return base->equals(power->base) && exponent->equals(power->exponent);
}

ExprPtr Power::clone() {
    return Power::from(base->clone(), exponent->clone());
}

ExprPtr Power::_derivative(char var) {
    bool baseIsNumber = base->isOfType(ExpressionType::CONSTANT);
    bool exponentIsNumber = exponent->isOfType(ExpressionType::CONSTANT);

    if (baseIsNumber && exponentIsNumber)// case b^k, where b and k are both numbers (constants)
        return Const::zero();

    if (!baseIsNumber && exponentIsNumber)// case [ f(x) ]^k, where k is a constant
    {
        auto* k = dynamic_cast<Const*>(exponent.get());

        // k*f^(k-1)*f'
        return Prod::from({
                exponent->clone(),                               // k
                base->derivative(var),                           // f'
                base->clone()->power(Const::n(k->getValue() - 1))// f^(k - 1)
        });
    }

    if (baseIsNumber)// case k^[ f(x) ], where k is a constant
    {
        // k^f * lnk * f'
        return Prod::from({
                this->clone(),            // a^f
                exponent->derivative(var),// f'
                Ln::from(base)            // lnk
        });
    }

    // otherwise: case [ f(x) ]^[ g(x) ], here we use the generalized power rule
    // [f(x)]^[g(x)] * ( g'*lnf + g*f'/f )
    return Prod::from({this->clone(),// [f(x)] ^ [g(x)]
                       Sum::from({   // g'*lnf + g*f'/f
                                  exponent->derivative(var)
                                          ->multiply(Ln::from(base)),// g'*lnf                                     // end g' * lnf
                                  exponent->clone()
                                          ->multiply(base->derivative(var)
                                                             ->divide(base->clone()))})});// g*f'/f
}

ExprPtr Power::simplified() {
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
                double value = Expr::evaluate();
                if (value < 10000.)
                    return Const::n(value);
            }
        }
    }
    if (base->isOfType(ExpressionType::DIVIDE)) {
        auto* frac = dynamic_cast<Divide*>(base.get());
        return frac->getDividend()->simplified()->power(exponent->simplified())->divide(frac->getDivisor()->simplified()->power(exponent->simplified()));
    }
    if (base->isOfType(ExpressionType::POWER)) {
        auto* pow = dynamic_cast<Power*>(base.get());
        return pow->getBase()->simplified()->power(pow->getExponent()->simplified()->multiply(exponent->simplified()));
    }
    if (base->isOfType(ExpressionType::PRODUCT)) {
        auto* prod = dynamic_cast<Prod*>(base.get());

        std::vector<ExprPtr> newFactors;
        newFactors.reserve(prod->getExpressionsSize());
        for (auto& factor: prod->getExpressions()) {
            newFactors.push_back(factor->simplified()
                                         ->power(exponent->simplified()));
        }

        return Prod::from(newFactors);
    }
    if (instanceof <Log>(base.get())) {
        auto* log = dynamic_cast<Log*>(base.get());
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
    return exponent->isOfType(ExpressionType::DIVIDE) || exponent->isOfType(ExpressionType::POWER) || instanceof <Operator>(exponent.get());
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
