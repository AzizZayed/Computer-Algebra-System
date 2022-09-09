//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Log.h"
#include "cas/CAS.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Expression.h"
#include "cas/node/Ln.h"
#include "cas/node/Product.h"

CAS_NAMESPACE

Log::Log(const ExpressionProperties& props, Expression* base, Expression* argument)
    : base(base), argument(argument), Expression(props) {
    base->setParent(this);
    argument->setParent(this);
}

Log::~Log() {
    delete base;
    delete argument;

    base = nullptr;
    argument = nullptr;
}

double Log::evaluate(const std::unordered_map<char, double>& variables) {
    return log(argument->evaluate(variables)) / log(base->evaluate(variables));
}

bool Log::equals(Expression* expression) {
    if (this == expression)
        return true;

    if (expression->isOfType(ExpressionType::LOGARITHM)) {
        auto* log = dynamic_cast<Log*>(expression);
        return base->equals(log->base) && argument->equals(log->argument);
    }
    return false;
}

Log* Log::clone() {
    return new Log(base->clone(), argument->clone());
}

Expression* Log::derivative(char var) {
    bool baseIsConstant = base->isOfType(ExpressionType::CONSTANT);
    bool argumentIsConstant = argument->isOfType(ExpressionType::CONSTANT);

    if (baseIsConstant && argumentIsConstant)
        return new Const(0);

    if (baseIsConstant) {
        return new Divide(
                argument->derivative(var),
                new Product({argument->clone(),
                             new Ln(base->clone())}));
    }

    Expression* exp = new Divide(new Ln(base->clone()), new Ln(argument->clone()));
    Expression* derivative = exp->derivative(var);

    delete exp;

    return derivative;
}

Expression* Log::simplified() {
    return new Log(base->simplified(), argument->simplified());// TODO: Simplify
}

bool Log::argumentNeedsParentheses() {
    return argument->isOfType(ExpressionType::SUM) || argument->isOfType(ExpressionType::PRODUCT) || argument->isOfType(ExpressionType::DIVIDE) || argument->isOfType(ExpressionType::POWER) || argument->isOfType(ExpressionType::LOGARITHM);
}

std::string Log::latex() {
    if (argumentNeedsParentheses())
        return "\\log_{" + base->latex() + "}{\\left(" + argument->latex() + "\\right)}";
    return "\\log_{" + base->latex() + "}{" + argument->latex() + "}";
}

std::wstring Log::stringify() {
    if (argumentNeedsParentheses()) {
        if (base->isOfType(ExpressionType::CONSTANT) || base->isOfType(ExpressionType::VARIABLE)) {
            return L"log_" + base->stringify() + L"(" + argument->stringify() + L")";
        }
        return L"log_(" + base->stringify() + L")(" + argument->stringify() + L")";
    }
    return L"log_" + base->stringify() + L" " + argument->stringify();
}

std::string Log::text() {
    return "log_(" + base->text() + ")_(" + argument->text() + ")";
}

std::string Log::explicitText() {
    return properties.getShortName() + "(" + base->explicitText() + ", " + argument->explicitText() + ")";
}

CAS_NAMESPACE_END