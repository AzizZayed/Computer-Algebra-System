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

TEST(ConstantNodeTest, ConstantCloneTest) {
    auto* constant = new cas::Constant(1);
    cas::Constant* constant2 = constant->clone(constant->getParent());
    EXPECT_EQ(constant->getValue(), constant2->getValue());
    EXPECT_EQ(constant->getExpressionType(), constant2->getExpressionType());
    EXPECT_EQ(constant->getParent(), constant2->getParent());
}

TEST(ConstantNodeTest, ConstantEvaluationTest) {
    auto* constant = new cas::Constant(cas::Constant::PI);
    EXPECT_EQ(cas::Constant::PI, constant->evaluate({}));
}

TEST(ConstantNodeTest, ConstantEqualsTest) {
    auto* constant = new cas::Constant(1);
    auto* constant2 = new cas::Constant(2);
    auto* constant3 = new cas::Constant(1);
    EXPECT_TRUE(constant->equals(constant3));
    EXPECT_FALSE(constant->equals(constant2));
}

TEST(ConstantNodeTest, ConstantDerivativeTest) {
    auto* constant = new cas::Constant(1);
    cas::ExpressionNode *derivative = constant->derivative(nullptr, 'x');
    EXPECT_EQ(0, ((cas::Constant*) derivative)->getValue());
}

TEST(ConstantNodeTest, ConstantSimplifiedTest) {
    auto* constant = new cas::Constant(1);
    EXPECT_TRUE(constant->equals(constant->simplified(nullptr)));
}

TEST(ConstantNodeTest, ConstantLatexTest) {
    auto* constant = new cas::Constant(1);
    EXPECT_EQ("1.000000", constant->latex());
}

TEST(ConstantNodeTest, ConstantStringifyTest) {
    auto* constant = new cas::Constant(1);
    EXPECT_EQ("1.000000", constant->stringify());
}

TEST(ConstantNodeTest, ConstantTextTest) {
    auto* constant = new cas::Constant(1);
    EXPECT_EQ("1.000000", constant->text());
}



