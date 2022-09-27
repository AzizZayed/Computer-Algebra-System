#include "cas/node/Abs.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "cas/node/trig/ArcSec.h"
#include "gtest/gtest.h"

TEST(ArcSecNodeTest, ArcSecCreateTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    EXPECT_EQ(node->getProperties().getType(), cas::ExpressionType::ARC_SEC);
    EXPECT_EQ(node->getProperties().getOrder(), uint16_t(cas::ExpressionType::ARC_SEC));
    EXPECT_EQ(node->getProperties().getName(), "arcsec");
    EXPECT_EQ(node->getProperties().getShortName(), "asec");
    EXPECT_EQ(node->getParent(), nullptr);
    EXPECT_TRUE(node->getArgument()->getParent()->equals(node));

    delete node;
}

TEST(ArcSecNodeTest, ArcSecDestroyTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    delete node;

    EXPECT_NE(node, nullptr);
}

TEST(ArcSecNodeTest, ArcSecEvaluateTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    EXPECT_EQ(node->evaluate({}), std::acos(1));

    auto* node2 = new cas::ArcSec(new cas::Const(-1));
    EXPECT_EQ(node2->evaluate({}), std::acos(-1));

    auto* node3 = new cas::ArcSec(new cas::Var);
    EXPECT_EQ(node3->evaluate({{'x', -1.0}}), std::acos(-1));

    delete node;
    delete node2;
}

TEST(ArcSecNodeTest, ArcSecEqualsTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    auto* node2 = new cas::ArcSec(new cas::Const(2));
    auto* node3 = new cas::ArcSec(new cas::Const(1));
    EXPECT_TRUE(node->equals(node3));
    EXPECT_TRUE(node->equals(node));
    EXPECT_FALSE(node->equals(node2));

    EXPECT_FALSE(node3->equals(node2));

    auto* var = new cas::Var('x');
    auto* node4 = new cas::ArcSec(var);
    auto* node5 = new cas::ArcSec(var->clone());
    EXPECT_TRUE(node4->equals(node5));

    delete node;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}

TEST(ArcSecNodeTest, ArcSecCloneTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    auto* clone = node->clone();
    EXPECT_TRUE(node->equals(clone));

    delete node;
    delete clone;
}

TEST(ArcSecNodeTest, ArcSecDerivativeTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    auto* derivative = node->derivative('x');
    EXPECT_TRUE(derivative->equals(new cas::Const(0)));

    auto* node2 = new cas::ArcSec(new cas::Var('x'));
    auto* derivative2 = node2->derivative('x');
    EXPECT_TRUE(derivative2->equals(
            cas::Const::one()
                    ->divide(cas::Var::x()
                                     ->abs()
                                     ->multiply(cas::Var::x()
                                                        ->power(2)
                                                        ->subtract(1)
                                                        ->sqrt()))));

    delete node;
    delete derivative;
    delete node2;
    delete derivative2;
}

TEST(ArcSecNodeTest, ArcSecSimplifiedTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    auto* simplified = node->simplified();
    EXPECT_TRUE(simplified->equals(node));

    auto* node2 = new cas::ArcSec(new cas::Var('x'));
    auto* simplified2 = node2->simplified();
    EXPECT_TRUE(simplified2->equals(new cas::ArcSec(new cas::Var('x'))));

    delete node;
    delete simplified;
    delete node2;
    delete simplified2;
}

TEST(ArcSecNodeTest, ArcSecLatexTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    EXPECT_EQ(node->latex(), "\\asec{1}");

    auto* node2 = new cas::ArcSec(new cas::Var('x'));
    EXPECT_EQ(node2->latex(), "\\asec{x}");

    delete node;
    delete node2;
}

TEST(ArcSecNodeTest, ArcSecStringifyTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    EXPECT_EQ(node->stringify(), L"asec 1");

    auto* node2 = new cas::ArcSec(new cas::Var('x'));
    EXPECT_EQ(node2->stringify(), L"asec x");

    delete node;
    delete node2;
}

TEST(ArcSecNodeTest, ArcSecTextTest) {
    auto* node = new cas::ArcSec(new cas::Const(1));
    EXPECT_EQ(node->text(), "asec(1)");

    auto* node2 = new cas::ArcSec(new cas::Var('x'));
    EXPECT_EQ(node2->text(), "asec(x)");

    delete node;
    delete node2;
}

TEST(ArcSecNodeTest, ArcSecExplicitTextTest) {
}
