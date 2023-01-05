//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "cas/node/Log.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Ln.h"
#include "cas/node/Power.h"
#include "cas/node/Prod.h"
#include "fmt/printf.h"
#include "fmt/xchar.h"

CAS_NAMESPACE

Log::Log(const ExpressionProperties& props, ExprPtr base, ExprPtr argument)
    : Expr(props), base(base), argument(argument) {
    base->setParent(this);
    argument->setParent(this);
}

Log::Log(ExprPtr base, ExprPtr argument)
    : Log({ExpressionType::LOGARITHM, "logarithm", "log"}, base, argument) {}

Log::Log(double base, ExprPtr argument)
    : Log({ExpressionType::LOGARITHM, "logarithm", "log"}, Const::n(base), argument) {}

Log::Log(ExprPtr argument)
    : Log({ExpressionType::LOGARITHM, "logarithm", "log"}, Const::n(10), argument) {}

double Log::evaluate(const VariableMap& variables) {
    return std::log(argument->evaluate(variables)) / std::log(base->evaluate(variables));
}

bool Log::_equals(ExprPtr expression) {
    if (expression->isOfType(ExpressionType::LOGARITHM)) {
        auto* log = dynamic_cast<Log*>(expression.get());
        return base->equals(log->base) && argument->equals(log->argument);
    }
    return false;
}

ExprPtr Log::clone() {
    return Log::from(base->clone(), argument->clone());
}

ExprPtr Log::_derivative(char var) {
    bool baseIsConstant = base->isOfType(ExpressionType::CONSTANT);
    bool argumentIsConstant = argument->isOfType(ExpressionType::CONSTANT);

    if (baseIsConstant && argumentIsConstant) {
        return Const::zero();
    }

    if (baseIsConstant) {
        return argument->derivative(var)
                ->divide(argument->clone()
                                 ->multiply(base->clone()->ln()));
    }

    ExprPtr exp = base->clone()
                          ->ln()
                          ->divide(argument->clone()
                                           ->ln());
    ExprPtr derivative = exp->derivative(var);

    return derivative;
}

ExprPtr Log::simplified() {
    if (argument->equals(base))
        return Const::one();

    if (argument->isOfType(ExpressionType::CONSTANT)) {
        double argumentValue = argument->evaluate();
        if (argumentValue == 1)
            return Const::zero();
    }

    if (argument->isOfType(ExpressionType::POWER)) {
        auto* power = dynamic_cast<Power*>(argument.get());
        if (power->getBase()->equals(base))
            return power->getExponent()->simplified();
    }

    return Log::from(base->simplified(), argument->simplified());
}

bool Log::argumentNeedsParentheses() {
    return argument->isOfType(ExpressionType::SUM) || argument->isOfType(ExpressionType::PRODUCT) || argument->isOfType(ExpressionType::DIVIDE) || argument->isOfType(ExpressionType::POWER) || argument->isOfType(ExpressionType::LOGARITHM);
}

std::string Log::latex() {
    if (argumentNeedsParentheses())
        return fmt::sprintf(R"(\log_{%s}{\left(%s\right)})", base->latex(), argument->latex());
    return fmt::sprintf("\\log_{%s}{%s}", base->latex(), argument->latex());
}

std::wstring Log::stringify() {
    if (argumentNeedsParentheses()) {
        if (base->isOfType(ExpressionType::CONSTANT) || base->isOfType(ExpressionType::VARIABLE)) {
            return fmt::format(L"log_{}({})", base->stringify(), argument->stringify());
        }
        return fmt::format(L"log({})({})", base->stringify(), argument->stringify());
    }
    return fmt::format(L"log_{} {}", base->stringify(), argument->stringify());
}

std::string Log::text() {
    return fmt::format("log_({})_({})", base->text(), argument->text());
}

std::string Log::explicitText() {
    return fmt::format("log({}, {})", base->explicitText(), argument->explicitText());
}

CAS_NAMESPACE_END