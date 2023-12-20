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
    return 1.0 / std::tan(arg->evaluate(variables));
}

Cot* Cot::clone() {
    return new Cot(arg->clone());
}

Expression* Cot::_derivative(char variable) {
    return new Negate(arg->clone()
                              ->csc()
                              ->power(2)
                              ->multiply(arg->derivative(variable)));
}

Expression* Cot::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        double value = arg->evaluate();
        if (unitCircle.contains(value)) {
            Expression* tan = unitCircle.at(value).tan;
            return tan->clone()->reciprocal();
        }
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->cot()->negate();
    }
    if (arg->isOfType(ExpressionType::ARC_COT)) {
        auto* arcCot = dynamic_cast<ArcCot*>(arg);
        return arcCot->getArgument()->simplified();
    }

    return arg->simplified()->cot();
}

CAS_NAMESPACE_END
