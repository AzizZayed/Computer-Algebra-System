#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Power.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "cas/node/trig/ArcTan.h"
#include "gtest/gtest.h"

TEST(ArcTanNodeTest, ArcTanCreateTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    EXPECT_EQ(node->getProperties().getType(), cas::ExpressionType::ARC_TAN);
    EXPECT_EQ(node->getProperties().getOrder(), uint16_t(cas::ExpressionType::ARC_TAN));
    EXPECT_EQ(node->getProperties().getName(), "arctan");
    EXPECT_EQ(node->getProperties().getShortName(), "atan");
    EXPECT_EQ(node->getParent(), nullptr);
    EXPECT_TRUE(node->getArgument()->getParent()->equals(node));

    delete node;
}

TEST(ArcTanNodeTest, ArcTanEvaluateTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    EXPECT_EQ(node->evaluate({}), std::atan(1));

    auto* node2 = new cas::ArcTan(new cas::Const(-1));
    EXPECT_EQ(node2->evaluate({}), std::atan(-1));

    auto* node3 = new cas::ArcTan(new cas::Var);
    EXPECT_EQ(node3->evaluate({{'x', -1.0}}), std::atan(-1));

    delete node;
    delete node2;
}

TEST(ArcTanNodeTest, ArcTanEqualsTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    auto* node2 = new cas::ArcTan(new cas::Const(2));
    auto* node3 = new cas::ArcTan(new cas::Const(1));
    EXPECT_TRUE(node->equals(node3));
    EXPECT_TRUE(node->equals(node));
    EXPECT_FALSE(node->equals(node2));

    EXPECT_FALSE(node3->equals(node2));

    auto* var = new cas::Var('x');
    auto* node4 = new cas::ArcTan(var);
    auto* node5 = new cas::ArcTan(var->clone());
    EXPECT_TRUE(node4->equals(node5));

    delete node;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}

TEST(ArcTanNodeTest, ArcTanCloneTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    auto* clone = node->clone();
    EXPECT_TRUE(node->equals(clone));

    delete node;
    delete clone;
}

TEST(ArcTanNodeTest, ArcTanDerivativeTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    auto* derivative = node->derivative('x');
    EXPECT_TRUE(derivative->equals(new cas::Const(0)));

    auto* node2 = new cas::ArcTan(new cas::Var('x'));
    auto* derivative2 = node2->derivative('x');
    EXPECT_TRUE(derivative2->equals(cas::Const::n(1)->divide(cas::Const::n(1)->add(cas::Var::x()->power(2)))));

    delete node;
    delete derivative;
    delete node2;
    delete derivative2;
}

TEST(ArcTanNodeTest, ArcTanSimplifiedTest) {
}

TEST(ArcTanNodeTest, ArcTanLatexTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    EXPECT_EQ(node->latex(), "\\text{arctan}{\\,1}");

    auto* node2 = new cas::ArcTan(new cas::Var('x'));
    EXPECT_EQ(node2->latex(), "\\text{arctan}{\\,x}");

    delete node;
    delete node2;
}

TEST(ArcTanNodeTest, ArcTanStringifyTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    EXPECT_EQ(node->stringify(), L"atan 1");

    auto* node2 = new cas::ArcTan(new cas::Var('x'));
    EXPECT_EQ(node2->stringify(), L"atan x");

    delete node;
    delete node2;
}

TEST(ArcTanNodeTest, ArcTanTextTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    EXPECT_EQ(node->text(), "atan(1)");

    auto* node2 = new cas::ArcTan(new cas::Var('x'));
    EXPECT_EQ(node2->text(), "atan(x)");

    delete node;
    delete node2;
}

TEST(ArcTanNodeTest, ArcTanExplicitTextTest) {
    auto* node = new cas::ArcTan(new cas::Const(1));
    EXPECT_EQ(node->explicitText(), "atan(const(1))");

    auto* node2 = new cas::ArcTan(new cas::Var('x'));
    EXPECT_EQ(node2->explicitText(), "atan(var(x))");

    delete node;
    delete node2;
}
