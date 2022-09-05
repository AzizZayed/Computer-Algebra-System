//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "gtest/gtest.h"
#include "core/CAS.h"
#include "core/node/Negate.h"
#include "core/node/Constant.h"
#include "core/node/Variable.h"

TEST(NegateNodeTest, NegateCreationTest) {
    auto* expression = new cas::Constant(5);
    auto* negate = new cas::Negate(expression);

    EXPECT_EQ(negate->getProperties().getType(), cas::ExpressionType::NEGATE);
    EXPECT_EQ(negate->getProperties().getName(), "negate");
    EXPECT_EQ(negate->getProperties().getShortName(), "neg");
    EXPECT_EQ(negate->getProperties().getOrder(), uint16_t(cas::ExpressionType::NEGATE));
    EXPECT_EQ(negate->getArgument()->equals(expression), true);
    EXPECT_EQ(negate->getParent(), nullptr);
    EXPECT_EQ(expression->getParent(), negate);

    delete negate;
}

TEST(NegateNodeTest, NegateDestroyTest) {
    auto* expression = new cas::Constant(5);
    auto* negate = new cas::Negate(expression);

    delete negate;

    EXPECT_NE(negate, nullptr);
}

TEST(NegateNodeTest, NegateCloneTest) {
    auto* expression = new cas::Constant(5);
    auto* negate = new cas::Negate(expression);
    auto* negate2 = negate->clone();

    EXPECT_EQ(negate->getProperties(), negate2->getProperties());
    EXPECT_TRUE(negate->getArgument()->equals(negate2->getArgument()));
    EXPECT_EQ(negate->getParent(), negate2->getParent());
    EXPECT_EQ(negate->getParent(), nullptr);

    delete negate;
    delete negate2;
}

TEST(NegateNodeTest, NegateEvaluationTest) {
    auto* expression = new cas::Constant(5);
    auto* negate = new cas::Negate(expression);

    EXPECT_EQ(negate->evaluate({}), -5);

    delete negate;
}

TEST(NegateNodeTest, NegateEqualsTest) {
    auto* expression = new cas::Constant(5);
    auto* negate = new cas::Negate(expression);
    auto* negate2 = new cas::Negate(expression);
    auto* negate3 = new cas::Negate(new cas::Constant(6));

    EXPECT_TRUE(negate->equals(negate));
    EXPECT_TRUE(negate->equals(negate2));
    EXPECT_FALSE(negate->equals(negate3));

    EXPECT_FALSE(negate->equals(new cas::Constant(1)));

    delete negate;
}

TEST(NegateNodeTest, NegateDerivativeTest) {
    auto* negate = new cas::Negate(new cas::Variable('x'));

    EXPECT_TRUE(negate->derivative('x')->equals(new cas::Negate(new cas::Constant(1))));

    delete negate;
}

TEST(NegateNodeTest, NegateStringifyTest) {
    auto* expression = new cas::Constant(5);
    auto* negate = new cas::Negate(expression);

    EXPECT_EQ(negate->stringify(), "-5.000000");

    delete negate;
}

TEST(NegateNodeTest, NegateSimplifiedTest) {
    auto* expression = new cas::Constant(5);
    auto* negate = new cas::Negate(expression);

    EXPECT_TRUE(negate->simplified()->equals(negate));

    delete negate;
}

TEST(NegateNodeTest, NegateSimplified2Test) {
    auto* expression = new cas::Constant(5);
    auto* negate = new cas::Negate(expression);
    auto* negate2 = new cas::Negate(negate);

    EXPECT_EQ(negate2->simplified()->equals(new cas::Constant(5)), true);

    delete negate;
}

