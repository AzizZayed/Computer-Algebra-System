//
// Created by Abd-El-Aziz Zayed on 2022-09-09.
//

#include "cas/node/Cbrt.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Product.h"
#include "cas/node/Var.h"
#include "gtest/gtest.h"

TEST(CbrtNodeTest, CbrtCreationTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_EQ(cbrt->getProperties().getType(), cas::ExpressionType::CUBE_ROOT);
    EXPECT_EQ(cbrt->getProperties().getName(), "cube_root");
    EXPECT_EQ(cbrt->getProperties().getShortName(), "cbrt");
    EXPECT_EQ(cbrt->getProperties().getOrder(), uint16_t(cas::ExpressionType::CUBE_ROOT));
    EXPECT_TRUE(cbrt->getBase()->equals(expression));
    EXPECT_EQ(cbrt->getParent(), nullptr);
    EXPECT_EQ(expression->getParent(), cbrt);

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtDestroyTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    delete cbrt;

    EXPECT_NE(cbrt, nullptr);
}

TEST(CbrtNodeTest, CbrtCloneTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);
    auto* cbrt2 = cbrt->clone();

    EXPECT_EQ(cbrt->getProperties(), cbrt2->getProperties());
    EXPECT_TRUE(cbrt->getBase()->equals(cbrt2->getBase()));
    EXPECT_EQ(cbrt->getParent(), cbrt2->getParent());
    EXPECT_EQ(cbrt->getParent(), nullptr);

    delete cbrt;
    delete cbrt2;
}

TEST(CbrtNodeTest, CbrtEvaluationTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_EQ(cbrt->evaluate({}), std::cbrt(5));

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtEqualsTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);
    auto* cbrt2 = new cas::Cbrt(expression->clone());

    EXPECT_TRUE(cbrt->equals(cbrt2));

    delete cbrt;
    delete cbrt2;
}

TEST(CbrtNodeTest, CbrtNotEqualsTest) {
    auto* expression = new cas::Const(5);
    auto* expression2 = new cas::Const(6);
    auto* cbrt = new cas::Cbrt(expression);
    auto* cbrt2 = new cas::Cbrt(expression2);

    EXPECT_FALSE(cbrt->equals(cbrt2));

    delete cbrt;
    delete cbrt2;
}

TEST(CbrtNodeTest, CbrtStringifyTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_EQ(cbrt->stringify(), L"cbrt(5)");

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtLatexTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_EQ(cbrt->latex(), "\\sqrt[3]{5}");

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtDerivativeTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_TRUE(cbrt->derivative('x')->equals(new cas::Const(0)));

    auto* expression2 = new cas::Var('x');
    auto* cbrt2 = new cas::Cbrt(expression2);
    EXPECT_TRUE(cbrt2->derivative('x')->equals(
            new cas::Divide(
                    new cas::Const(1),
                    new cas::Product({new cas::Const(3), new cas::Cbrt(new cas::Power(expression2->clone(), 2))}))));

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtSimplifiedTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_TRUE(cbrt->simplified()->equals(cbrt->clone()));

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtSimplified2Test) {
    auto* expression = new cas::Const(27);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_TRUE(cbrt->simplified()->equals(new cas::Const(3)));

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtSimplified3Test) {
    auto* expression = new cas::Const(1);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_FALSE(cbrt->simplified()->equals(new cas::Var('x')));

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtTextTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_EQ(cbrt->text(), "cbrt(5)");

    delete cbrt;
}

TEST(CbrtNodeTest, CbrtExplicitTextTest) {
    auto* expression = new cas::Const(5);
    auto* cbrt = new cas::Cbrt(expression);

    EXPECT_EQ(cbrt->explicitText(), "cbrt(const(5))");

    delete cbrt;
}
