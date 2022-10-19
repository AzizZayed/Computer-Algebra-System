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
#include "cas/util/StringUtils.h"
#include <fmt/printf.h>
#include <fmt/xchar.h>

CAS_NAMESPACE

const std::unordered_map<double, UnitCircleCoordinate> TrigExpression::unitCircle = {
        {0, {0, Const::one(), Const::zero(), Const::zero()}},
        {math::PI_6, {math::PI_6, Const::n(3)->sqrt()->divide(2), Const::n(1)->divide(2), Const::one()->divide(Const::n(3)->sqrt())}},
        {math::PI_4, {math::PI_4, Const::n(2)->sqrt()->divide(2), Const::n(2)->sqrt()->divide(2), Const::one()}},
        {math::PI_3, {math::PI_3, Const::n(1)->divide(2), Const::n(3)->sqrt()->divide(2), Const::n(3)->sqrt()}},
        {math::PI_2, {math::PI_2, Const::zero(), Const::one(), Const::n(math::POSITIVE_INFINITY)}},
        {math::PI_2_3, {math::PI_2_3, Const::n(-1)->divide(2), Const::n(3)->sqrt()->divide(2), Const::n(3)->sqrt()->negate()}},
        {math::PI_3_4, {math::PI_3_4, Const::n(2)->sqrt()->negate()->divide(2), Const::n(2)->sqrt()->divide(2), Const::n(-1)}},
        {math::PI_5_6, {math::PI_5_6, Const::n(3)->sqrt()->negate()->divide(2), Const::n(1)->divide(2), Const::n(-1)->divide(Const::n(3)->sqrt())}},
        {math::PI, {math::PI, Const::n(-1), Const::zero(), Const::zero()}},
        {math::PI_7_6, {math::PI_7_6, Const::n(3)->sqrt()->negate()->divide(2), Const::n(-1)->divide(2), Const::one()->divide(Const::n(3)->sqrt())}},
        {math::PI_5_4, {math::PI_5_4, Const::n(2)->sqrt()->negate()->divide(2), Const::n(2)->sqrt()->negate()->divide(2), Const::one()}},
        {math::PI_4_3, {math::PI_4_3, Const::n(-1)->divide(2), Const::n(3)->sqrt()->negate()->divide(2), Const::n(3)->sqrt()}},
        {math::PI_3_2, {math::PI_3_2, Const::zero(), Const::n(-1), Const::n(math::POSITIVE_INFINITY)}},
        {math::PI_5_3, {math::PI_5_3, Const::n(1)->divide(2), Const::n(3)->sqrt()->negate()->divide(2), Const::n(3)->sqrt()->negate()}},
        {math::PI_7_4, {math::PI_7_4, Const::n(2)->sqrt()->divide(2), Const::n(2)->sqrt()->negate()->divide(2), Const::n(-1)}},
        {math::PI_11_6, {math::PI_11_6, Const::n(3)->sqrt()->divide(2), Const::n(-1)->divide(2), Const::n(-1)->divide(Const::n(3)->sqrt())}},
};

TrigExpression::TrigExpression(const ExpressionProperties& properties, Expression* argument)
    : UnaryExpression(properties, argument) {}

bool TrigExpression::_equals(Expression* other) {
    auto* otherTrigFunction = dynamic_cast<TrigExpression*>(other);
    return argument->equals(otherTrigFunction->argument);
}

bool TrigExpression::needsParentheses() {
    return instanceof <Operator>(argument) || instanceof <Log>(argument) || argument->isOfType(ExpressionType::POWER) || argument->isOfType(ExpressionType::DIVIDE);
}

std::string TrigExpression::latex() {
    if (needsParentheses())
        return fmt::sprintf("%s{\\left(%s\\right)}", properties.getShortName(), argument->latex());
    return fmt::sprintf("\\%s{%s}", properties.getShortName(), argument->latex());
}

std::wstring TrigExpression::stringify() {
    if (needsParentheses())
        return fmt::format(L"{} ({})", toWstring(properties.getShortName()), argument->stringify());
    return fmt::format(L"{} {}", toWstring(properties.getShortName()), argument->stringify());
}

CAS_NAMESPACE_END
