//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "core/CAS.h"
#include "core/node/Power.h"
#include "core/node/Constant.h"
#include "core/node/Product.h"
#include "core/node/Ln.h"
#include "core/node/Sum.h"
#include "core/node/Divide.h"
#include "core/node/Negate.h"

CAS_NAMESPACE

Power::Power(Expression* base, Expression* exponent)
: Expression({ExpressionType::POWER, "power", "pow"}), base(base), exponent(exponent)
{
    this->base->setParent(this);
    this->exponent->setParent(this);
}

Power::~Power()
{
#if CAS_DEBUG
    printf("Destroy Power\n");
#endif

    delete base;
    delete exponent;
}

double Power::evaluate(const std::unordered_map<char, double>& variables) {
    return pow(base->evaluate(variables), exponent->evaluate(variables));
}

bool Power::equals(Expression* expression) {
    if (expression->isOfType(ExpressionType::POWER)) {
        auto* power = dynamic_cast<Power*>(expression);
        return base->equals(power->base) && exponent->equals(power->exponent);
    }

    return false;
}

Power* Power::clone() {
    return new Power(base->clone(), exponent->clone());
}

Expression * Power::derivative(char var) {
    bool baseIsNumber = base->isOfType(ExpressionType::CONSTANT);
    bool exponentIsNumber = exponent->isOfType(ExpressionType::CONSTANT);

    if (baseIsNumber && exponentIsNumber) // case b^k, where b and k are both numbers (constants)
        return new Constant(0);

    if (!baseIsNumber && exponentIsNumber) // case [ f(x) ]^k, where k is a constant
    {
        auto* k = dynamic_cast<Constant*>(exponent);

        return new Product({ // k*f^(k-1)*f'
            exponent->clone(), // k
            base->derivative(var), // f'
            new Power( // f^(k - 1)
                base->clone(), // f
                new Constant(k->getValue() - 1) // k - 1
            ) // end f^(k - 1)
        }); // end k*f^(k-1)*f'
    }

    if (baseIsNumber) // case k^[ f(x) ], where k is a constant
    {
        return new Product({ // k^f * lnk * f'
            this->clone(), // a^f
            exponent->derivative(var), // f'
            new Negate(base) // lnk // TODO replace negate with ln
        }); // end k^f * lnk * f'
    }

    // otherwise: case [ f(x) ]^[ g(x) ], here we use the generalized power rule
    return new Product({ // [f(x)]^[g(x)] * ( g'*lnf + g*f'/f )
        this->clone(), // [f(x)] ^ [g(x)]
        new Sum({ // g'*lnf + g*f'/f
            new Product({ // g' * lnf
                exponent->derivative(var), // g'
                new Negate(base) // lnf // TODO replace negate with ln
            }), // end g' * lnf
            new Product({ // g * f' * 1/f
                exponent->clone(), // g
                new Divide( // f'/f
                    base->derivative(var), // f'
                    base->clone() // f
                ) // end f'/f
            }) // end g*f'/f
        }) // end g'*lnf + g*f'/f
    }); // end [f(x)]^[g(x)] * ( g'*lnf + g*f'/f)
}

Expression* Power::simplified() {
    return clone(); // TODO implement simplified
}

bool Power::baseNeedsParentheses() {
    return !(base->isOfType(ExpressionType::CONSTANT) || base->isOfType(ExpressionType::VARIABLE));
}

bool Power::exponentNeedsParentheses() {
    return exponent->isOfType(ExpressionType::DIVIDE)
    || exponent->isOfType(ExpressionType::POWER)
    || instanceof<Operator>(exponent);
}

std::string Power::latex()
{
    if (baseNeedsParentheses())
        return "\\left(" + base->latex() + "\\right)^{" + exponent->latex() + "}";
    return base->latex() + "^{" + exponent->latex() + "}";
}

std::string Power::stringify()
{
    if (baseNeedsParentheses()) {
        if (exponentNeedsParentheses())
            return "(" + base->stringify() + ")^(" + exponent->stringify() + ")";
        else
            return "(" + base->stringify() + ")^" + exponent->stringify();
    } else {
        if (exponentNeedsParentheses())
            return base->stringify() + "^(" + exponent->stringify() + ")";
        else
            return base->stringify() + "^" + exponent->stringify();
    }
}

std::string Power::text() {
    return "(" + base->text() + ")^(" + exponent->text() + ")";
}

std::string Power::explicitText() {
    return properties.getShortName() + "(" + base->explicitText() + ", " + exponent->explicitText() + ")";
}

CAS_NAMESPACE_END

