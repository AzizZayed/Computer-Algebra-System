#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "cas/node/trig/ArcSin.h"
#include "gtest/gtest.h"

TEST(ArcSinNodeTest, ArcSinCreateTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    EXPECT_EQ(node->getProperties().getType(), cas::ExpressionType::ARC_SIN);
    EXPECT_EQ(node->getProperties().getOrder(), uint16_t(cas::ExpressionType::ARC_SIN));
    EXPECT_EQ(node->getProperties().getName(), "arcsin");
    EXPECT_EQ(node->getProperties().getShortName(), "asin");
    EXPECT_EQ(node->getParent(), nullptr);
    EXPECT_TRUE(node->getArgument()->getParent()->equals(node));

    delete node;
}

TEST(ArcSinNodeTest, ArcSinEvaluateTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    EXPECT_EQ(node->evaluate({}), std::asin(1));

    auto* node2 = new cas::ArcSin(new cas::Const(-1));
    EXPECT_EQ(node2->evaluate({}), std::asin(-1));

    auto* node3 = new cas::ArcSin(new cas::Var);
    EXPECT_EQ(node3->evaluate({{'x', -1.0}}), std::asin(-1));

    delete node;
    delete node2;
}

TEST(ArcSinNodeTest, ArcSinEqualsTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    auto* node2 = new cas::ArcSin(new cas::Const(2));
    auto* node3 = new cas::ArcSin(new cas::Const(1));
    EXPECT_TRUE(node->equals(node3));
    EXPECT_TRUE(node->equals(node));
    EXPECT_FALSE(node->equals(node2));

    EXPECT_FALSE(node3->equals(node2));

    auto* var = new cas::Var('x');
    auto* node4 = new cas::ArcSin(var);
    auto* node5 = new cas::ArcSin(var->clone());
    EXPECT_TRUE(node4->equals(node5));

    delete node;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}

TEST(ArcSinNodeTest, ArcSinCloneTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    auto* clone = node->clone();
    EXPECT_TRUE(node->equals(clone));

    delete node;
    delete clone;
}

TEST(ArcSinNodeTest, ArcSinDerivativeTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    auto* derivative = node->derivative('x');
    EXPECT_TRUE(derivative->equals(new cas::Const(0)));

    auto* node2 = new cas::ArcSin(new cas::Var('x'));
    auto* derivative2 = node2->derivative('x');
    EXPECT_TRUE(derivative2->equals(
            cas::Const::n(1)->divide(cas::Const::n(1)->subtract(cas::Var::x()->power(2))->sqrt())));

    delete node;
    delete derivative;
    delete node2;
    delete derivative2;
}

TEST(ArcSinNodeTest, ArcSinSimplifiedTest) {
}

TEST(ArcSinNodeTest, ArcSinLatexTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    EXPECT_EQ(node->latex(), "\\text{arcsin}{\\,1}");

    auto* node2 = new cas::ArcSin(new cas::Var('x'));
    EXPECT_EQ(node2->latex(), "\\text{arcsin}{\\,x}");

    delete node;
    delete node2;
}

TEST(ArcSinNodeTest, ArcSinStringifyTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    EXPECT_EQ(node->stringify(), L"asin 1");

    auto* node2 = new cas::ArcSin(new cas::Var('x'));
    EXPECT_EQ(node2->stringify(), L"asin x");

    delete node;
    delete node2;
}

TEST(ArcSinNodeTest, ArcSinTextTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    EXPECT_EQ(node->text(), "asin(1)");

    auto* node2 = new cas::ArcSin(new cas::Var('x'));
    EXPECT_EQ(node2->text(), "asin(x)");

    delete node;
    delete node2;
}

TEST(ArcSinNodeTest, ArcSinExplicitTextTest) {
    auto* node = new cas::ArcSin(new cas::Const(1));
    EXPECT_EQ(node->explicitText(), "asin(const(1))");

    auto* node2 = new cas::ArcSin(new cas::Var('x'));
    EXPECT_EQ(node2->explicitText(), "asin(var(x))");

    delete node;
    delete node2;
}
