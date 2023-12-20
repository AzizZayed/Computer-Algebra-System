//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#include "cas/node/trig/TrigExpression.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Log.h"
#include "cas/node/Negate.h"
#include "cas/node/Operator.h"
#include "cas/node/Sqrt.h"
#include <fmt/printf.h>

CAS_NAMESPACE

const std::unordered_map<double, UnitCircleCoordinate> TrigExpression::unitCircle = {
        {0, {0, Const::one(), Const::zero(), Const::zero()}},
        {math_constants::PI_6, {math_constants::PI_6, Const::n(3)->sqrt()->divide(2), Const::n(1)->divide(2), Const::one()->divide(Const::n(3)->sqrt())}},
        {math_constants::PI_4, {math_constants::PI_4, Const::n(2)->sqrt()->divide(2), Const::n(2)->sqrt()->divide(2), Const::one()}},
        {math_constants::PI_3, {math_constants::PI_3, Const::n(1)->divide(2), Const::n(3)->sqrt()->divide(2), Const::n(3)->sqrt()}},
        {math_constants::PI_2, {math_constants::PI_2, Const::zero(), Const::one(), Const::n(math_constants::POSITIVE_INFINITY)}},
        {math_constants::PI_2_3, {math_constants::PI_2_3, Const::n(-1)->divide(2), Const::n(3)->sqrt()->divide(2), Const::n(3)->sqrt()->negate()}},
        {math_constants::PI_3_4, {math_constants::PI_3_4, Const::n(2)->sqrt()->negate()->divide(2), Const::n(2)->sqrt()->divide(2), Const::n(-1)}},
        {math_constants::PI_5_6, {math_constants::PI_5_6, Const::n(3)->sqrt()->negate()->divide(2), Const::n(1)->divide(2), Const::n(-1)->divide(Const::n(3)->sqrt())}},
        {math_constants::PI, {math_constants::PI, Const::n(-1), Const::zero(), Const::zero()}},
        {math_constants::PI_7_6, {math_constants::PI_7_6, Const::n(3)->sqrt()->negate()->divide(2), Const::n(-1)->divide(2), Const::one()->divide(Const::n(3)->sqrt())}},
        {math_constants::PI_5_4, {math_constants::PI_5_4, Const::n(2)->sqrt()->negate()->divide(2), Const::n(2)->sqrt()->negate()->divide(2), Const::one()}},
        {math_constants::PI_4_3, {math_constants::PI_4_3, Const::n(-1)->divide(2), Const::n(3)->sqrt()->negate()->divide(2), Const::n(3)->sqrt()}},
        {math_constants::PI_3_2, {math_constants::PI_3_2, Const::zero(), Const::n(-1), Const::n(math_constants::POSITIVE_INFINITY)}},
        {math_constants::PI_5_3, {math_constants::PI_5_3, Const::n(1)->divide(2), Const::n(3)->sqrt()->negate()->divide(2), Const::n(3)->sqrt()->negate()}},
        {math_constants::PI_7_4, {math_constants::PI_7_4, Const::n(2)->sqrt()->divide(2), Const::n(2)->sqrt()->negate()->divide(2), Const::n(-1)}},
        {math_constants::PI_11_6, {math_constants::PI_11_6, Const::n(3)->sqrt()->divide(2), Const::n(-1)->divide(2), Const::n(-1)->divide(Const::n(3)->sqrt())}},
};

TrigExpression::TrigExpression(const ExpressionProperties& properties, Expression* argument)
    : UnaryExpression(properties, argument) {}

bool TrigExpression::_equals(Expression* other) {
    auto* otherTrigFunction = dynamic_cast<TrigExpression*>(other);
    return arg->equals(otherTrigFunction->arg);
}

bool TrigExpression::needsParentheses() {
    return instanceof <Operator>(arg) || instanceof <Log>(arg) || arg->isOfType(ExpressionType::POWER) || arg->isOfType(ExpressionType::DIVIDE);
}

std::string TrigExpression::latex() {
    if (needsParentheses())
        return fmt::sprintf(R"(\%s{\left(%s\right)})", properties.getShortName(), arg->latex());
    return fmt::sprintf("\\%s{%s}", properties.getShortName(), arg->latex());
}

std::string TrigExpression::str() {
    if (needsParentheses())
        return fmt::format("{} ({})", properties.getShortName(), arg->str());
    return fmt::format("{} {}", properties.getShortName(), arg->str());
}

CAS_NAMESPACE_END
