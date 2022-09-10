#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "cas/node/trig/ArcCos.h"
#include "gtest/gtest.h"

TEST(ArcCosNodeTest, ArcCosCreateTest) {
    auto* node = new cas::ArcCos(new cas::Const(1));
    EXPECT_EQ(node->getProperties().getType(), cas::ExpressionType::ARC_COS);
    EXPECT_EQ(node->getProperties().getOrder(), uint16_t(cas::ExpressionType::ARC_COS));
    EXPECT_EQ(node->getProperties().getName(), "arccos");
    EXPECT_EQ(node->getProperties().getShortName(), "acos");
    EXPECT_EQ(node->getParent(), nullptr);
    EXPECT_TRUE(node->getArgument()->getParent()->equals(node));

    delete node;
}

TEST(ArcCosNodeTest, ArcCosDestroyTest) {
    auto* node = new cas::ArcCos(new cas::Const(1));
    delete node;

    EXPECT_NE(node, nullptr);
}

TEST(ArcCosNodeTest, ArcCosEvaluateTest) {
    auto* node = new cas::ArcCos(new cas::Const(1));
    EXPECT_EQ(node->evaluate({}), 0);

    auto* node2 = new cas::ArcCos(new cas::Const(-1));
    EXPECT_EQ(node2->evaluate({}), std::acos(-1));

    auto* node3 = new cas::ArcCos(new cas::Var);
    EXPECT_EQ(node3->evaluate({{'x', -1.0}}), std::acos(-1));

    delete node;
    delete node2;
}

TEST(ArcCosNodeTest, ArcCosEqualsTest) {
    auto* node = new cas::ArcCos(new cas::Const(1));
    auto* node2 = new cas::ArcCos(new cas::Const(2));
    auto* node3 = new cas::ArcCos(new cas::Const(1));
    EXPECT_TRUE(node->equals(node3));
    EXPECT_TRUE(node->equals(node));
    EXPECT_FALSE(node->equals(node2));

    EXPECT_FALSE(node3->equals(node2));

    auto* var = new cas::Var('x');
    auto* node4 = new cas::ArcCos(var);
    auto* node5 = new cas::ArcCos(var->clone());
    EXPECT_TRUE(node4->equals(node5));

    delete node;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}

TEST(ArcCosNodeTest, ArcCosCloneTest) {
    auto* node = new cas::ArcCos(new cas::Const(1));
    cas::ArcCos* node2 = node->clone();
    EXPECT_EQ(node->getProperties().getType(), node2->getProperties().getType());
    EXPECT_EQ(node->getProperties().getOrder(), node2->getProperties().getOrder());
    EXPECT_EQ(node->getProperties().getName(), node2->getProperties().getName());
    EXPECT_EQ(node->getProperties().getShortName(), node2->getProperties().getShortName());
    EXPECT_EQ(node->getParent(), node2->getParent());
    EXPECT_EQ(node->getParent(), nullptr);
    EXPECT_TRUE(node->getArgument()->equals(node2->getArgument()));
    delete node2;
    delete node;
}

TEST(ArcCosNodeTest, ArcCosDerivativeTest) {
    cas::Expression* node = new cas::ArcCos(new cas::Const(1));
    auto* node2 = new cas::ArcCos(new cas::Var);
    auto* node3 = new cas::ArcCos(new cas::Const(2));
    auto* node4 = new cas::ArcCos(new cas::Var('x'));

    auto* zero = new cas::Const(0);
    EXPECT_TRUE(node->derivative('x')->equals(zero));
    EXPECT_TRUE(node3->derivative('x')->equals(zero));

    EXPECT_TRUE(node2->derivative('x')->equals(
            (new cas::Const(1))
                    ->negate()
                    ->divide(
                            (new cas::Const(1))
                                    ->subtract((new cas::Var)->power(2))
                                    ->sqrt())));
    EXPECT_TRUE(node4->derivative('y')->equals(zero));

    delete node;
    delete node2;
    delete node3;
    delete node4;
}

TEST(ArcCosNodeTest, ArcCosSimplifiedTest) {
    auto* node3 = new cas::ArcCos(new cas::Var);
    auto* node4 = new cas::ArcCos(new cas::Var('x'));

    EXPECT_TRUE(node3->simplified()->equals(node3));
    EXPECT_TRUE(node4->simplified()->equals(node4));

    delete node3;
    delete node4;
}

TEST(ArcCosNodeTest, ArcCosLatexTest) {
    auto* node1 = new cas::ArcCos(new cas::Const(1));
    auto* node2 = new cas::ArcCos(new cas::Var);
    auto* node3 = new cas::ArcCos(new cas::Const(2));
    auto* node4 = new cas::ArcCos(new cas::Var('x'));

    EXPECT_EQ(node1->latex(), "\\acos{1}");
    EXPECT_EQ(node2->latex(), "\\acos{x}");
    EXPECT_EQ(node3->latex(), "\\acos{2}");
    EXPECT_EQ(node4->latex(), "\\acos{x}");

    delete node1;
    delete node2;
    delete node3;
    delete node4;
}

TEST(ArcCosNodeTest, ArcCosStringifyTest) {
    auto* node1 = new cas::ArcCos(new cas::Const(1));
    auto* node2 = new cas::ArcCos(new cas::Var);
    auto* node3 = new cas::ArcCos(new cas::Const(2));
    auto* node4 = new cas::ArcCos(new cas::Var('x'));

    EXPECT_EQ(node1->stringify(), L"acos 1");
    EXPECT_EQ(node2->stringify(), L"acos x");
    EXPECT_EQ(node3->stringify(), L"acos 2");
    EXPECT_EQ(node4->stringify(), L"acos x");

    delete node1;
    delete node2;
    delete node3;
    delete node4;
}

TEST(ArcCosNodeTest, ArcCosTextTest) {
    auto* node1 = new cas::ArcCos(new cas::Const(1));
    auto* node2 = new cas::ArcCos(new cas::Var);
    auto* node3 = new cas::ArcCos(new cas::Const(2));
    auto* node4 = new cas::ArcCos(new cas::Var('x'));

    EXPECT_EQ(node1->text(), "acos(1)");
    EXPECT_EQ(node2->text(), "acos(x)");
    EXPECT_EQ(node3->text(), "acos(2)");
    EXPECT_EQ(node4->text(), "acos(x)");

    delete node1;
    delete node2;
    delete node3;
    delete node4;
}

TEST(ArcCosNodeTest, ArcCosExplicitTextTest) {
    auto* node1 = new cas::ArcCos(new cas::Const(1));
    auto* node2 = new cas::ArcCos(new cas::Var);
    auto* node3 = new cas::ArcCos(new cas::Const(2));
    auto* node4 = new cas::ArcCos(new cas::Var('x'));

    EXPECT_EQ(node1->explicitText(), "acos(const(1))");
    EXPECT_EQ(node2->explicitText(), "acos(var(x))");
    EXPECT_EQ(node3->explicitText(), "acos(const(2))");
    EXPECT_EQ(node4->explicitText(), "acos(var(x))");

    delete node1;
    delete node2;
    delete node3;
    delete node4;
}
