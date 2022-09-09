//
// Created by Abd-El-Aziz Zayed on 2022-08-29.
//

#include "cas/node/Const.h"
#include "cas/node/Var.h"
#include "gtest/gtest.h"

TEST(ConstantNodeTest, ConstantCreationTest) {
    auto* constant = new cas::Const(1);
    EXPECT_EQ(1, constant->getValue());
    EXPECT_EQ(cas::ExpressionType::CONSTANT, constant->getProperties().getType());
    EXPECT_EQ("constant", constant->getProperties().getName());
    EXPECT_EQ("const", constant->getProperties().getShortName());
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
    EXPECT_EQ("1", constant->latex());
}

TEST(ConstantNodeTest, ConstantStringifyTest) {
    cas::Const* constant = cas::Const::PI();
    //    EXPECT_EQ(L"π", constant->stringify());
    EXPECT_TRUE(wcscmp(cas::Const::PI_UNICODE, constant->stringify().c_str()) == 0);

    constant = cas::Const::E();
    //    EXPECT_EQ(L"e", constant->stringify());
    EXPECT_TRUE(wcscmp(cas::Const::E_UNICODE, constant->stringify().c_str()) == 0);

    constant = cas::Const::PHI();
    //    EXPECT_EQ(L"ϕ", constant->stringify());
    EXPECT_TRUE(wcscmp(cas::Const::PHI_UNICODE, constant->stringify().c_str()) == 0);

    constant = new cas::Const(1);
    //    EXPECT_EQ(L"1.000000", constant->stringify());
    EXPECT_TRUE(wcscmp(L"1", constant->stringify().c_str()) == 0);
}

TEST(ConstantNodeTest, ConstantTextTest) {
    auto* constant = new cas::Const(1);
    EXPECT_EQ("1", constant->text());
}

TEST(ConstantNodeTest, ConstantExplicitTextTest) {
    auto* constant = new cas::Const(1);
    EXPECT_EQ("const(1)", constant->explicitText());
}
