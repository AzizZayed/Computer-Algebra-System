//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#include "core/node/Constant.h"
#include "core/node/Variable.h"
#include "gtest/gtest.h"

TEST(VariableNodeTest, VariableCreationTest) {
    auto *variable = new cas::Variable('x');
    EXPECT_EQ('x', variable->getSymbol());
    EXPECT_EQ(cas::ExpressionType::VARIABLE, variable->getProperties().getType());
    EXPECT_EQ(nullptr, variable->getParent());
}

TEST(VariableNodeTest, VariableDestroyTest) {
    auto *variable = new cas::Variable;
    delete variable;

    EXPECT_NE(variable, nullptr);
}

TEST(VariableNodeTest, VariableCloneTest) {
    auto *variable = new cas::Variable('x');
    cas::Variable *variable2 = variable->clone();
    EXPECT_EQ(variable->getSymbol(), variable2->getSymbol());
    EXPECT_EQ(variable->getProperties().getType(), variable2->getProperties().getType());
    EXPECT_EQ(variable->getParent(), variable2->getParent());
    EXPECT_EQ(variable->getParent(), nullptr);
}

TEST(VariableNodeTest, VariableEvaluationTest) {
    auto *variable = new cas::Variable('x');
    std::unordered_map<char, double> map = {{'x', 1}};

    EXPECT_NE(0, variable->evaluate(map));
    EXPECT_EQ(1, variable->evaluate(map));

    EXPECT_THROW({
        try {
            variable->evaluate({});
        } catch (std::runtime_error &e) {
            EXPECT_STREQ("Variable not found for evaluation", e.what());
            throw;
        }
    },
                 std::runtime_error);
}

TEST(VariableNodeTest, VariableEqualsTest) {
    auto *variable = new cas::Variable('x');
    auto *variable2 = new cas::Variable('x');
    auto *variable3 = new cas::Variable('y');
    EXPECT_TRUE(variable->equals(variable2));
    EXPECT_FALSE(variable->equals(variable3));

    EXPECT_FALSE(variable->equals(new cas::Constant(1)));
}

TEST(VariableNodeTest, VariableDerivativeTest) {
    auto *variable = new cas::Variable('x');
    cas::Constant *derivative = variable->derivative('x');
    EXPECT_EQ(1, derivative->getValue());

    cas::Constant *derivative2 = variable->derivative('y');
    EXPECT_EQ(0, derivative2->getValue());
}

TEST(VariableNodeTest, VariableSimplifiedTest) {
    auto *variable = new cas::Variable('x');
    EXPECT_TRUE(variable->equals(variable->simplified()));
}

TEST(VariableNodeTest, VariableLatexTest) {
    auto *variable = new cas::Variable('x');
    EXPECT_EQ("x", variable->latex());
}

TEST(VariableNodeTest, VariableStringifyTest) {
    auto *variable = new cas::Variable('x');
    EXPECT_EQ("x", variable->stringify());
}

TEST(VariableNodeTest, VariableTextTest) {
    auto *variable = new cas::Variable('x');
    EXPECT_EQ("x", variable->text());
}

TEST(VariableNodeTest, VariableExplicitTextTest) {
    auto *variable = new cas::Variable('x');
    EXPECT_EQ("var(x)", variable->explicitText());
}
