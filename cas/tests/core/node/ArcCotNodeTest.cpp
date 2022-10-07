#include "cas/node/Const.h"
#include "cas/node/Var.h"
#include "cas/node/trig/ArcCot.h"
#include "gtest/gtest.h"

TEST(ArcCotNodeTest, ArcCotCreateTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    EXPECT_EQ(node->getProperties().getType(), cas::ExpressionType::ARC_COT);
    EXPECT_EQ(node->getProperties().getOrder(), uint16_t(cas::ExpressionType::ARC_COT));
    EXPECT_EQ(node->getProperties().getName(), "arccot");
    EXPECT_EQ(node->getProperties().getShortName(), "acot");
    EXPECT_EQ(node->getParent(), nullptr);
    EXPECT_TRUE(node->getArgument()->getParent()->equals(node));

    delete node;
}

TEST(ArcCotNodeTest, ArcCotDestroyTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    delete node;

    EXPECT_NE(node, nullptr);
}

TEST(ArcCotNodeTest, ArcCotEvaluateTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    EXPECT_EQ(node->evaluate({}), std::atan(1));

    auto* node2 = new cas::ArcCot(new cas::Const(-1));
    EXPECT_EQ(node2->evaluate({}), std::atan(-1));

    auto* node3 = new cas::ArcCot(new cas::Var);
    EXPECT_EQ(node3->evaluate({{'x', 2.0}}), std::atan(1.0 / 2.0));

    delete node;
    delete node2;
}

TEST(ArcCotNodeTest, ArcCotEqualsTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    auto* node2 = new cas::ArcCot(new cas::Const(2));
    auto* node3 = new cas::ArcCot(new cas::Const(1));
    EXPECT_TRUE(node->equals(node3));
    EXPECT_TRUE(node->equals(node));
    EXPECT_FALSE(node->equals(node2));

    EXPECT_FALSE(node3->equals(node2));

    auto* var = new cas::Var('x');
    auto* node4 = new cas::ArcCot(var);
    auto* node5 = new cas::ArcCot(var->clone());
    EXPECT_TRUE(node4->equals(node5));

    delete node;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}

TEST(ArcCotNodeTest, ArcCotCloneTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    auto* node2 = node->clone();
    EXPECT_TRUE(node->equals(node2));

    delete node;
    delete node2;
}

TEST(ArcCotNodeTest, ArcCotDerivativeTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    auto* node2 = node->derivative('x');
    EXPECT_TRUE(node2->equals(new cas::Const(0)));

    delete node;
    delete node2;
}

TEST(ArcCotNodeTest, ArcCotSimplifiedTest) {
    auto* node3 = new cas::ArcCot(new cas::Var('x'));
    auto* node4 = node3->simplified();
    EXPECT_TRUE(node4->equals(new cas::ArcCot(new cas::Var('x'))));

    delete node3;
    delete node4;
}

TEST(ArcCotNodeTest, ArcCotLatexTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    EXPECT_EQ(node->latex(), "\\text{arccot}{\\,1}");

    auto* node2 = new cas::ArcCot(new cas::Var('x'));
    EXPECT_EQ(node2->latex(), "\\text{arccot}{\\,x}");

    delete node;
    delete node2;
}

TEST(ArcCotNodeTest, ArcCotStringifyTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    EXPECT_EQ(node->stringify(), L"acot 1");

    auto* node2 = new cas::ArcCot(new cas::Var('x'));
    EXPECT_EQ(node2->stringify(), L"acot x");

    delete node;
    delete node2;
}

TEST(ArcCotNodeTest, ArcCotTextTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    EXPECT_EQ(node->text(), "acot(1)");

    auto* node2 = new cas::ArcCot(new cas::Var('x'));
    EXPECT_EQ(node2->text(), "acot(x)");

    delete node;
    delete node2;
}

TEST(ArcCotNodeTest, ArcCotExplicitTextTest) {
    auto* node = new cas::ArcCot(new cas::Const(1));
    EXPECT_EQ(node->explicitText(), "acot(const(1))");

    auto* node2 = new cas::ArcCot(new cas::Var('x'));
    EXPECT_EQ(node2->explicitText(), "acot(var(x))");

    delete node;
    delete node2;
}
