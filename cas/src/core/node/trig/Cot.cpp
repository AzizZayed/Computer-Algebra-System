//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Cot.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/trig/ArcCot.h"
#include "cas/node/trig/Csc.h"
#include "cas/node/trig/Sec.h"

CAS_NAMESPACE

Cot::Cot(Expression* argument) : TrigExpression({ExpressionType::COT, "cotangent", "cot"}, argument) {}

double Cot::evaluate(const VariableMap& variables) {
    return 1.0 / std::tan(argument->evaluate(variables));
}

Cot* Cot::clone() {
    return new Cot(argument->clone());
}

Expression* Cot::_derivative(char variable) {
    return new Negate(argument->clone()
                              ->csc()
                              ->power(2)
                              ->multiply(argument->derivative(variable)));
}

Expression* Cot::simplified() {
    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double value = argument->evaluate();
        if (unitCircle.contains(value)) {
            Expression* tan = unitCircle.at(value).tan;
            return tan->clone()->reciprocal();
        }
    }
    if (argument->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(argument);
        return negate->getArgument()->simplified()->cot()->negate();
    }
    if (argument->isOfType(ExpressionType::ARC_COT)) {
        auto* arcCot = dynamic_cast<ArcCot*>(argument);
        return arcCot->getArgument()->simplified();
    }

    return argument->simplified()->cot();
}

CAS_NAMESPACE_END
