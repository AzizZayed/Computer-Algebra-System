#include "cas/node/Abs.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Prod.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "cas/node/trig/ArcCsc.h"
#include "gtest/gtest.h"

TEST(ArcCscNodeTest, ArcCscCreateTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    EXPECT_EQ(node->getProperties().getType(), cas::ExpressionType::ARC_CSC);
    EXPECT_EQ(node->getProperties().getOrder(), uint16_t(cas::ExpressionType::ARC_CSC));
    EXPECT_EQ(node->getProperties().getName(), "arccsc");
    EXPECT_EQ(node->getProperties().getShortName(), "acsc");
    EXPECT_EQ(node->getParent(), nullptr);
    EXPECT_TRUE(node->getArgument()->getParent()->equals(node));

    delete node;
}

TEST(ArcCscNodeTest, ArcCscDestroyTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    delete node;

    EXPECT_NE(node, nullptr);
}

TEST(ArcCscNodeTest, ArcCscEvaluateTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    EXPECT_EQ(node->evaluate({}), std::asin(1));

    auto* node2 = new cas::ArcCsc(new cas::Const(-1));
    EXPECT_EQ(node2->evaluate({}), std::asin(-1));

    auto* node3 = new cas::ArcCsc(new cas::Var);
    EXPECT_EQ(node3->evaluate({{'x', -1.0}}), std::asin(-1));

    delete node;
    delete node2;
}

TEST(ArcCscNodeTest, ArcCscEqualsTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    auto* node2 = new cas::ArcCsc(new cas::Const(2));
    auto* node3 = new cas::ArcCsc(new cas::Const(1));
    EXPECT_TRUE(node->equals(node3));
    EXPECT_TRUE(node->equals(node));
    EXPECT_FALSE(node->equals(node2));

    EXPECT_FALSE(node3->equals(node2));

    auto* var = new cas::Var('x');
    auto* node4 = new cas::ArcCsc(var);
    auto* node5 = new cas::ArcCsc(var->clone());
    EXPECT_TRUE(node4->equals(node5));

    delete node;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}

TEST(ArcCscNodeTest, ArcCscCloneTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    auto* clone = node->clone();
    EXPECT_TRUE(node->equals(clone));

    delete node;
    delete clone;
}

TEST(ArcCscNodeTest, ArcCscDerivativeTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    auto* derivative = node->derivative('x');
    EXPECT_TRUE(derivative->equals(new cas::Const(0)));

    auto* node2 = new cas::ArcCsc(new cas::Var('x'));
    auto* derivative2 = node2->derivative('x');
    EXPECT_TRUE(derivative2->equals(
            cas::Const::one()
                    ->negate()
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

TEST(ArcCscNodeTest, ArcCscSimplifiedTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    auto* simplified = node->simplified();
    EXPECT_TRUE(simplified->equals(node));

    auto* node2 = new cas::ArcCsc(new cas::Var('x'));
    auto* simplified2 = node2->simplified();
    EXPECT_TRUE(simplified2->equals(new cas::ArcCsc(cas::Var::x())));

    delete node;
    delete simplified;
    delete node2;
    delete simplified2;
}

TEST(ArcCscNodeTest, ArcCscLatexTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    EXPECT_EQ(node->latex(), "\\text{arccsc}{\\,1}");

    auto* node2 = new cas::ArcCsc(new cas::Var('x'));
    EXPECT_EQ(node2->latex(), "\\text{arccsc}{\\,x}");

    delete node;
    delete node2;
}

TEST(ArcCscNodeTest, ArcCscStringifyTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    EXPECT_EQ(node->stringify(), L"acsc 1");

    auto* node2 = new cas::ArcCsc(new cas::Var('x'));
    EXPECT_EQ(node2->stringify(), L"acsc x");

    delete node;
    delete node2;
}

TEST(ArcCscNodeTest, ArcCscTextTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    EXPECT_EQ(node->text(), "acsc(1)");

    auto* node2 = new cas::ArcCsc(new cas::Var('x'));
    EXPECT_EQ(node2->text(), "acsc(x)");

    delete node;
    delete node2;
}

TEST(ArcCscNodeTest, ArcCscExplicitTextTest) {
    auto* node = new cas::ArcCsc(new cas::Const(1));
    EXPECT_EQ(node->explicitText(), "acsc(const(1))");

    auto* node2 = new cas::ArcCsc(new cas::Var('x'));
    EXPECT_EQ(node2->explicitText(), "acsc(var(x))");

    delete node;
    delete node2;
}
