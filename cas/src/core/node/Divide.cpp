//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "core/CAS.h"
#include "core/node/Expression.h"
#include "core/node/Divide.h"
#include "core/node/Sum.h"
#include "core/node/Product.h"
#include "core/node/Constant.h"
#include "core/node/Power.h"

CAS_NAMESPACE

Divide::Divide(Expression* parent, Expression* dividend, Expression* divisor)
: Expression(parent, {ExpressionType::DIVIDE, "divide", "div"}), dividend(dividend), divisor(divisor) {}

Divide::~Divide()
{
#if DEBUG_CAS
    printf("Destroy cas::Divide\n");
#endif

    delete dividend;
    delete divisor;
}

double Divide::evaluate(const std::unordered_map<char, double>& variables)
{
    return dividend->evaluate(variables) / divisor->evaluate(variables);
}

bool Divide::equals(Expression* expression)
{
    if (expression->getProperties().getType() == ExpressionType::DIVIDE) {
        Divide* divide = dynamic_cast<Divide*>(expression);
        return dividend->equals(divide->dividend) && divisor->equals(divide->divisor);
    }

    return false;
}

Divide* Divide::clone(Expression* newParent)
{
    return new Divide(newParent, dividend->clone(), divisor->clone());
}

Divide* Divide::derivative(Expression* newParent, char variable)
{
    return new Divide( // quotient rule
            new Sum({ // f'g - fg'
                new Product({ // f'g
                    dividend->derivative(nullptr, variable), // f'g
                    divisor->clone() // g
                }), // end f'*g
                new Product({ // -fg' // TODO negate this instead
                    new Constant(-1), // -1
                    dividend->clone(), // f
                    divisor->derivative(nullptr, variable) // g'
                }) // end -fg'
            }), // end f'g - fg'
            new Power( // g^2
                    divisor, // g
                    new Constant(2) // 2
            ) // end g^2
    ); // end quotient rule
}

Expression* Divide::simplified(Expression* newParent)
{
    Expression* dividendSimplified = dividend->simplified(newParent);
    Expression* divisorSimplified = divisor->simplified(newParent);

    // TODO simplify

    return new Divide(newParent, dividendSimplified, divisorSimplified);
}

std::string Divide::latex()
{
    return "\\dfrac{" + dividend->latex() + "}{" + divisor->latex() + "}";
}

std::string Divide::stringify()
{
    return "(" + dividend->stringify() + "/" + divisor->stringify() + ")";
}

std::string Divide::text()
{
    return "((" + dividend->text() + ")/(" + divisor->text() + "))";
}

std::string Divide::explicitText()
{
    return properties.getShortName() + "(" + dividend->explicitText() + ", " + divisor->explicitText() + ")";
}

CAS_NAMESPACE_END