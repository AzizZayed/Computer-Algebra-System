//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "core/node/Sum.h"
#include "core/node/Variable.h"
#include "gtest/gtest.h"

TEST(SumNodeTest, SumCreationTest) {
    std::vector<cas::Expression*> expressions = {new cas::Variable('x'), new cas::Variable('y')};
    auto* sum = new cas::Sum(expressions);
    EXPECT_EQ(cas::ExpressionType::SUM, sum->getProperties().getType());
    EXPECT_EQ("summation", sum->getProperties().getName());
    EXPECT_EQ("sum", sum->getProperties().getShortName());
    EXPECT_EQ('+', sum->getSymbol());
    EXPECT_EQ(2, sum->getExpressions().size());
    EXPECT_EQ(nullptr, sum->getParent());

    for (cas::Expression* exp: expressions) {
        EXPECT_EQ(sum, exp->getParent());
    }

    delete sum;
}

TEST(SumNodeTest, SumDestroyTest) {
    auto* sum = new cas::Sum({new cas::Variable('x'), new cas::Variable('y')});
    delete sum;

    EXPECT_NE(sum, nullptr);
}

TEST(SumNodeTest, SumCloneTest) {
    auto* sum = new cas::Sum({new cas::Variable('x'), new cas::Variable('y')});
    cas::Sum* sum2 = sum->clone();
    EXPECT_EQ(sum->getProperties().getType(), sum2->getProperties().getType());
    EXPECT_EQ(sum->getProperties().getName(), sum2->getProperties().getName());
    EXPECT_EQ(sum->getProperties().getShortName(), sum2->getProperties().getShortName());
    EXPECT_EQ(sum->getSymbol(), sum2->getSymbol());
    EXPECT_EQ(sum->getExpressions().size(), sum2->getExpressions().size());
    EXPECT_EQ(sum->getParent(), sum2->getParent());
    EXPECT_EQ(sum->getParent(), nullptr);
}

TEST(SumNodeTest, SumEvaluationTest) {
    auto* sum = new cas::Sum({new cas::Variable('x'), new cas::Variable('y')});
    std::unordered_map<char, double> map = {{'x', 1},
                                            {'y', 2}};

    EXPECT_NE(0, sum->evaluate(map));
    EXPECT_EQ(3, sum->evaluate(map));
}

TEST(SumNodeTest, SumEqualsTest) {
    auto* sum = new cas::Sum({new cas::Variable('x'), new cas::Variable('y')});
    auto* sum2 = new cas::Sum({new cas::Variable('x'), new cas::Variable('y')});
    auto* sum3 = new cas::Sum({new cas::Variable('x'), new cas::Variable('z')});
    EXPECT_TRUE(sum->equals(sum2));
    EXPECT_FALSE(sum->equals(sum3));

    EXPECT_FALSE(sum->equals(new cas::Constant(1)));
}

TEST(SumNodeTest, SumDerivativeTest) {
    auto* sum = new cas::Sum({new cas::Variable('x'), new cas::Variable('y')});
    cas::Sum* derivative = sum->derivative('x');
    EXPECT_EQ(cas::ExpressionType::SUM, derivative->getProperties().getType());
    EXPECT_EQ(2, derivative->getExpressions().size());
    // TODO test deeper

    // TODO test deeper
}

TEST(SumNodeTest, SumSimplifiedTest) {
    // test when complete
}

TEST(SumNodeTest, SumLatexTest) {
    auto* sum = new cas::Sum({new cas::Variable('x'), new cas::Variable('y'), cas::Constant::PI()});
    EXPECT_EQ("x + y + \\pi", sum->latex());
}

TEST(SumNodeTest, SumStringifyTest) {
    auto* sum = new cas::Sum({new cas::Variable('x'), new cas::Variable('y'), cas::Constant::PI()});
    EXPECT_EQ("x + y + π", sum->stringify());
}
