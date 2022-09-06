//
// Created by Abd-El-Aziz Zayed on 2022-08-29.
//

#include "core/node/Const.h"
#include "core/node/Var.h"
#include "gtest/gtest.h"

TEST(ConstantNodeTest, ConstantCreationTest) {
    auto* constant = new cas::Const(1);
    EXPECT_EQ(1, constant->getValue());
    EXPECT_EQ(cas::ExpressionType::CONSTANT, constant->getProperties().getType());
    EXPECT_EQ(nullptr, constant->getParent());

    auto* constant2 = new cas::Const(2);
    constant2->setParent(constant);
    EXPECT_EQ(2, constant2->getValue());
    EXPECT_EQ(cas::ExpressionType::CONSTANT, constant2->getProperties().getType());
    EXPECT_EQ(constant, constant2->getParent());
}

TEST(ConstantNodeTest, ConstantDestroyTest) {
    auto* constant = new cas::Const;
    delete constant;

    EXPECT_NE(constant, nullptr);
}

TEST(ConstantNodeTest, ConstantCloneTest) {
    auto* constant = new cas::Const(1);
    cas::Const* constant2 = constant->clone();
    EXPECT_EQ(constant->getValue(), constant2->getValue());
    EXPECT_EQ(constant->getProperties().getType(), constant2->getProperties().getType());
    EXPECT_EQ(constant->getParent(), constant2->getParent());
    EXPECT_EQ(constant->getParent(), nullptr);
}

TEST(ConstantNodeTest, ConstantEvaluationTest) {
    auto* constant = cas::Const::PI();
    EXPECT_EQ(cas::math::PI, constant->evaluate({}));
}

TEST(ConstantNodeTest, ConstantEqualsTest) {
    auto* constant = new cas::Const(1);
    auto* constant2 = new cas::Const(2);
    auto* constant3 = new cas::Const(1);
    EXPECT_TRUE(constant->equals(constant3));
    EXPECT_FALSE(constant->equals(constant2));

    EXPECT_FALSE(constant->equals(new cas::Var('x')));
}

TEST(ConstantNodeTest, ConstantDerivativeTest) {
    auto* constant = new cas::Const(1);
    cas::Expression* derivative = constant->derivative('x');
    EXPECT_EQ(0, ((cas::Const*) derivative)->getValue());
}

TEST(ConstantNodeTest, ConstantSimplifiedTest) {
    auto* constant = new cas::Const(1);
    EXPECT_TRUE(constant->equals(constant->simplified()));
}

TEST(ConstantNodeTest, ConstantLatexTest) {
    cas::Const* constant = cas::Const::PI();
    EXPECT_EQ("\\pi", constant->latex());

    constant = cas::Const::E();
    EXPECT_EQ("e", constant->latex());

    constant = cas::Const::PHI();
    EXPECT_EQ("\\varphi", constant->latex());

    constant = new cas::Const(1);
    EXPECT_EQ("1.000000", constant->latex());
}

TEST(ConstantNodeTest, ConstantStringifyTest) {
    cas::Const* constant = cas::Const::PI();
    EXPECT_EQ("π", constant->stringify());

    constant = cas::Const::E();
    EXPECT_EQ("e", constant->stringify());

    constant = cas::Const::PHI();
    EXPECT_EQ("ϕ", constant->stringify());

    constant = new cas::Const(1);
    EXPECT_EQ("1.000000", constant->stringify());
}

TEST(ConstantNodeTest, ConstantTextTest) {
    auto* constant = new cas::Const(1);
    EXPECT_EQ("1.000000", constant->text());
}

TEST(ConstantNodeTest, ConstantExplicitTextTest) {
    auto* constant = new cas::Const(1);
    EXPECT_EQ("const(1.000000)", constant->explicitText());
}
