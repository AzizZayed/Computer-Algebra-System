//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Tan.h"
#include "cas/node/Const.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/trig/ArcTan.h"
#include "cas/node/trig/Sec.h"

CAS_NAMESPACE

Tan::Tan(Expression* argument) : TrigExpression({ExpressionType::TAN, "tangent", "tan"}, argument) {}

double Tan::evaluate(const VariableMap& variables) {
    return std::tan(arg->evaluate(variables));
}

Tan* Tan::clone() {
    return new Tan(arg->clone());
}

Expression* Tan::_derivative(char variable) {
    Expression* derivative = arg->derivative(variable);
    return arg->clone()->sec()->power(2)->multiply(derivative);
}

Expression* Tan::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        double value = arg->evaluate();
        if (unitCircle.contains(value))
            return unitCircle.at(value).tan->clone();
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->tan()->negate();
    }
    if (arg->isOfType(ExpressionType::ARC_TAN)) {
        auto* arcTan = dynamic_cast<ArcTan*>(arg);
        return arcTan->getArgument()->simplified();
    }

    return arg->simplified()->tan();
}

CAS_NAMESPACE_END
