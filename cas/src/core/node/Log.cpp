//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Log.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Ln.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "fmt/printf.h"

CAS_NAMESPACE

Log::Log(const ExpressionProperties& props, Expression* base, Expression* argument)
    : Expression(props), base(base), argument(argument) {
    base->setParent(this);
    argument->setParent(this);
}

Log::Log(Expression* base, Expression* argument)
    : Log({ExpressionType::LOGARITHM, "logarithm", "log"}, base, argument) {}

Log::Log(double base, Expression* argument)
    : Log({ExpressionType::LOGARITHM, "logarithm", "log"}, new Const(base), argument) {}

Log::Log(Expression* argument)
    : Log({ExpressionType::LOGARITHM, "logarithm", "log"}, Const::n(10), argument) {}

Log::~Log() {
    delete base;
    delete argument;

    base = nullptr;
    argument = nullptr;
}

double Log::evaluate(const VariableMap& variables) {
    return std::log(argument->evaluate(variables)) / std::log(base->evaluate(variables));
}

bool Log::_equals(Expression* expression) {
    if (expression->isOfType(ExpressionType::LOGARITHM)) {
        auto* log = dynamic_cast<Log*>(expression);
        return base->equals(log->base) && argument->equals(log->argument);
    }
    return false;
}

Log* Log::clone() {
    return new Log(base->clone(), argument->clone());
}

Expression* Log::_derivative(char var) {
    bool baseIsConstant = base->isOfType(ExpressionType::CONSTANT);
    bool argumentIsConstant = argument->isOfType(ExpressionType::CONSTANT);

    if (baseIsConstant && argumentIsConstant) {
        return new Const(0);
    }

    if (baseIsConstant) {
        return argument->derivative(var)
                ->divide(argument->clone()
                                 ->multiply(base->clone()->ln()));
    }

    Expression* exp = base->clone()
                              ->ln()
                              ->divide(argument->clone()
                                               ->ln());
    Expression* derivative = exp->derivative(var);

    delete exp;

    return derivative;
}

Expression* Log::simplified() {
    if (argument->equals(base))
        return Const::one();

    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double argumentValue = argument->evaluate();
        if (argumentValue == 1)
            return Const::zero();
    }

    if (argument->isOfType(ExpressionType::POWER)) {
        auto* power = dynamic_cast<Power*>(argument);
        if (power->getBase()->equals(base))
            return power->getExponent()->simplified();
    }

    return new Log(base->simplified(), argument->simplified());
}

bool Log::argumentNeedsParentheses() {
    return argument->isOfType(ExpressionType::SUM) || argument->isOfType(ExpressionType::PRODUCT) || argument->isOfType(ExpressionType::DIVIDE) || argument->isOfType(ExpressionType::POWER) || argument->isOfType(ExpressionType::LOGARITHM);
}

std::string Log::latex() {
    if (argumentNeedsParentheses())
        return fmt::sprintf(R"(\log_{%s}{\left(%s\right)})", base->latex(), argument->latex());
    return fmt::sprintf("\\log_{%s}{%s}", base->latex(), argument->latex());
}

std::string Log::str() {
    if (argumentNeedsParentheses()) {
        if (base->isOfType(ExpressionType::CONSTANT) || base->isOfType(ExpressionType::VARIABLE)) {
            return fmt::format("log_{}({})", base->str(), argument->str());
        }
        return fmt::format("log({})({})", base->str(), argument->str());
    }
    return fmt::format("log_{} {}", base->str(), argument->str());
}

std::string Log::text() {
    return fmt::format("log_({})_({})", base->text(), argument->text());
}

std::string Log::explicitText() {
    return fmt::format("log({}, {})", base->explicitText(), argument->explicitText());
}

CAS_NAMESPACE_END