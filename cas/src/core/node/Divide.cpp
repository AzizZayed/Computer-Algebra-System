//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "core/node/Divide.h"
#include "core/CAS.h"
#include "core/node/Const.h"
#include "core/node/Expression.h"
#include "core/node/Negate.h"
#include "core/node/Power.h"
#include "core/node/Product.h"
#include "core/node/Sum.h"

CAS_NAMESPACE

Divide::Divide(Expression* dividend, Expression* divisor)
    : Expression({ExpressionType::DIVIDE, "divide", "div"}), dividend(dividend), divisor(divisor) {
    this->dividend->setParent(this);
    this->divisor->setParent(this);
}

Divide::~Divide() {
#if DEBUG_CAS
    printf("Destroy cas::Divide\n");
#endif

    delete dividend;
    delete divisor;

    dividend = nullptr;
    divisor = nullptr;
}

double Divide::evaluate(const std::unordered_map<char, double>& variables) {
    return dividend->evaluate(variables) / divisor->evaluate(variables);
}

bool Divide::equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->isOfType(ExpressionType::DIVIDE)) {
        auto* divide = dynamic_cast<Divide*>(expression);
        return dividend->equals(divide->dividend) && divisor->equals(divide->divisor);
    }

    return false;
}

Divide* Divide::clone() {
    return new Divide(dividend->clone(), divisor->clone());
}

Divide* Divide::derivative(char var) {
    return new Divide(// quotient rule
            new Sum({
                    // f'g - fg'
                    new Product({
                            // f'g
                            dividend->derivative(var),// f'g
                            divisor->clone()          // g
                    }),                               // end f'*g
                    new Negate(new Product({
                            // -fg'
                            dividend->clone(),      // f
                            divisor->derivative(var)// g'
                    }))                             // end -fg'
            }),                                     // end f'g - fg'
            new Power(                              // g^2
                    divisor->clone(),               // g
                    new Const(2)                    // 2
                    )                               // end g^2
    );                                              // end quotient rule
}

Expression* Divide::simplified() {
    Expression* dividendSimplified = dividend->simplified();
    Expression* divisorSimplified = divisor->simplified();

    // TODO simplify

    return new Divide(dividendSimplified, divisorSimplified);
}

std::string Divide::latex() {
    return "\\dfrac{" + dividend->latex() + "}{" + divisor->latex() + "}";
}

std::string Divide::stringify() {
    return "(" + dividend->stringify() + "/" + divisor->stringify() + ")";
}

std::string Divide::text() {
    return "((" + dividend->text() + ")/(" + divisor->text() + "))";
}

std::string Divide::explicitText() {
    return properties.getShortName() + "(" + dividend->explicitText() + ", " + divisor->explicitText() + ")";
}

CAS_NAMESPACE_END