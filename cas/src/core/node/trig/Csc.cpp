//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/Csc.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
#include "cas/node/trig/ArcCsc.h"
#include "cas/node/trig/Cot.h"

CAS_NAMESPACE

Csc::Csc(Expression* argument) : TrigExpression({ExpressionType::CSC, "cosecant", "csc"}, argument) {}

double Csc::evaluate(const VariableMap& variables) {
    return 1.0 / std::sin(arg->evaluate(variables));
}

Csc* Csc::clone() {
    return new Csc(arg->clone());
}

Expression* Csc::_derivative(char variable) {
    Expression* derivative = arg->derivative(variable);
    Product* p = new Product({arg->clone()->csc(), arg->clone()->cot(), derivative});
    return p->negate();
}

Expression* Csc::simplified() {
    if (arg->isOfType(ExpressionType::CONSTANT)) {
        double value = arg->evaluate();
        if (unitCircle.contains(value)) {
            Expression* sin = unitCircle.at(value).sin;
            return sin->clone()->reciprocal();
        }
    }
    if (arg->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(arg);
        return negate->getArgument()->simplified()->csc()->negate();
    }
    if (arg->isOfType(ExpressionType::ARC_CSC)) {
        auto* arcCsc = dynamic_cast<ArcCsc*>(arg);
        return arcCsc->getArgument()->simplified();
    }

    return arg->simplified()->csc();
}

CAS_NAMESPACE_END
