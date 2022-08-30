//
// Created by Abd-El-Aziz Zayed on 2022-08-29.
//

#include "gtest/gtest.h"
#include "core/node/Constant.h"

TEST(ConstantNodeTest, ConstantCreationTest) {
    auto* constant = new cas::Constant(1);
    EXPECT_EQ(1, constant->getValue());
    EXPECT_EQ(cas::ExpressionType::CONSTANT, constant->getExpressionType());
    EXPECT_EQ(nullptr, constant->getParent());

    auto* constant2 = new cas::Constant(constant, 2);
    EXPECT_EQ(2, constant2->getValue());
    EXPECT_EQ(cas::ExpressionType::CONSTANT, constant2->getExpressionType());
    EXPECT_EQ(constant, constant2->getParent());
}

TEST(ConstantNodeTest, ConstantDestroyTest) {
    auto* constant = new cas::Constant;
    delete constant;

    EXPECT_NE(constant, nullptr);
}

TEST(ConstantNodeTest, ConstantCloneTest) {
    auto* constant = new cas::Constant(1);
    cas::Constant* constant2 = constant->clone();
    EXPECT_EQ(constant->getValue(), constant2->getValue());
    EXPECT_EQ(constant->getExpressionType(), constant2->getExpressionType());
    EXPECT_EQ(constant->getParent(), constant2->getParent());
    EXPECT_EQ(constant->getParent(), nullptr);
}

TEST(ConstantNodeTest, ConstantEvaluationTest) {
    auto* constant = cas::Constant::PI();
    EXPECT_EQ(cas::math::PI, constant->evaluate({}));
}

TEST(ConstantNodeTest, ConstantEqualsTest) {
    auto* constant = new cas::Constant(1);
    auto* constant2 = new cas::Constant(2);
    auto* constant3 = new cas::Constant(1);
    EXPECT_TRUE(constant->equals(constant3));
    EXPECT_FALSE(constant->equals(constant2));

    // TODO test with another expression type to increase branch coverage
}

TEST(ConstantNodeTest, ConstantDerivativeTest) {
    auto* constant = new cas::Constant(1);
    cas::Expression *derivative = constant->derivative(nullptr, 'x');
    EXPECT_EQ(0, ((cas::Constant*) derivative)->getValue());
}

TEST(ConstantNodeTest, ConstantSimplifiedTest) {
    auto* constant = new cas::Constant(1);
    EXPECT_TRUE(constant->equals(constant->simplified(nullptr)));
}

TEST(ConstantNodeTest, ConstantLatexTest) {
    cas::Constant* constant = cas::Constant::PI();
    EXPECT_EQ("\\pi", constant->latex());

    constant = cas::Constant::E();
    EXPECT_EQ("e", constant->latex());

    constant = cas::Constant::PHI();
    EXPECT_EQ("\\varphi", constant->latex());

    constant = new cas::Constant(1);
    EXPECT_EQ("1.000000", constant->latex());
}

TEST(ConstantNodeTest, ConstantStringifyTest) {
    cas::Constant* constant = cas::Constant::PI();
    EXPECT_EQ("π", constant->stringify());

    constant = cas::Constant::E();
    EXPECT_EQ("e", constant->stringify());

    constant = cas::Constant::PHI();
    EXPECT_EQ("ϕ", constant->stringify());

    constant = new cas::Constant(1);
    EXPECT_EQ("1.000000", constant->stringify());
}

TEST(ConstantNodeTest, ConstantTextTest) {
    auto* constant = new cas::Constant(1);
    EXPECT_EQ("1.000000", constant->text());
}

TEST(ConstantNodeTest, ConstantFullTextTest) {
    auto* constant = new cas::Constant(1);
    EXPECT_EQ("constant(1.000000)", constant->fullText());
}



