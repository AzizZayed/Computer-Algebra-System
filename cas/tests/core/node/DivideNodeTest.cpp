//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#include "core/node/Divide.h"
#include "core/node/Negate.h"
#include "core/node/Power.h"
#include "core/node/Product.h"
#include "core/node/Sum.h"
#include "core/node/Variable.h"
#include "gtest/gtest.h"

TEST(DivideNodeTest, DivideCreationTest) {
    auto *numerator = new cas::Variable('x');
    auto *denominator = new cas::Variable('y');
    auto *divide = new cas::Divide(numerator, denominator);
    EXPECT_EQ(cas::ExpressionType::DIVIDE, divide->getProperties().getType());
    EXPECT_EQ("divide", divide->getProperties().getName());
    EXPECT_EQ("div", divide->getProperties().getShortName());
    EXPECT_EQ(nullptr, divide->getParent());

    EXPECT_EQ(numerator->getParent(), divide);
    EXPECT_EQ(denominator->getParent(), divide);

    delete divide;
}

TEST(DivideNodeTest, DivideDestroyTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    delete divide;

    EXPECT_NE(divide, nullptr);
}

TEST(DivideNodeTest, DivideCloneTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    cas::Divide *divide2 = divide->clone();
    EXPECT_EQ(divide->getProperties().getType(), divide2->getProperties().getType());
    EXPECT_EQ(divide->getProperties().getName(), divide2->getProperties().getName());
    EXPECT_EQ(divide->getProperties().getShortName(), divide2->getProperties().getShortName());
    EXPECT_EQ(divide->getParent(), divide2->getParent());
    EXPECT_EQ(divide->getParent(), nullptr);
}

TEST(DivideNodeTest, DivideEvaluationTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    std::unordered_map<char, double> map = {{'x', 1},
                                            {'y', 2}};

    EXPECT_NE(0, divide->evaluate(map));
    EXPECT_EQ(0.5, divide->evaluate(map));
}

TEST(DivideNodeTest, DivideEqualsTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    auto *divide2 = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    auto *divide3 = new cas::Divide(new cas::Variable('x'), new cas::Variable('z'));
    EXPECT_TRUE(divide->equals(divide2));
    EXPECT_FALSE(divide->equals(divide3));

    EXPECT_FALSE(divide->equals(new cas::Constant(1)));
}

TEST(DivideNodeTest, DivideDerivativeTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    auto *divide2 = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));

    EXPECT_TRUE(divide->derivative('x')->equals(divide2->derivative('x')));
    EXPECT_TRUE(divide->derivative('y')->equals(divide2->derivative('y')));

    EXPECT_FALSE(divide->derivative('x')->equals(divide2->derivative('y')));

    EXPECT_TRUE(divide->derivative('x')->equals(
            new cas::Divide(// quotient rule
                    new cas::Sum({
                            // f'g - fg'
                            new cas::Product({
                                    // f'g
                                    new cas::Constant(1), // f'
                                    new cas::Variable('y')// g
                            }),                           // end f'*g
                            new cas::Negate(new cas::Product({
                                    // -fg'
                                    new cas::Variable('x'),// f
                                    new cas::Constant(0)   // g'
                            }))                            // end -fg'
                    }),                                    // end f'g - fg'
                    new cas::Power(                        // g^2
                            new cas::Variable('y'),        // g
                            new cas::Constant(2)           // 2
                            )                              // end g^2
                    )                                      // end quotient rule
            ));
    EXPECT_TRUE(divide->derivative('y')->equals(
            new cas::Divide(// quotient rule
                    new cas::Sum({
                            // f'g - fg'
                            new cas::Product({
                                    // f'g
                                    new cas::Constant(0), // f'
                                    new cas::Variable('y')// g
                            }),                           // end f'*g
                            new cas::Negate(new cas::Product({
                                    // -fg'
                                    new cas::Variable('x'),// f
                                    new cas::Constant(1)   // g'
                            }))                            // end -fg'
                    }),                                    // end f'g - fg'
                    new cas::Power(                        // g^2
                            new cas::Variable('y'),        // g
                            new cas::Constant(2)           // 2
                            )                              // end g^2
                    )                                      // end quotient rule
            ));
}

TEST(DivideNodeTest, DivideSimplifiedTest) {
    // TODO - add simplified test
}

TEST(DivideNodeTest, DivideLatexTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    EXPECT_EQ("\\dfrac{x}{y}", divide->latex());
}

TEST(DivideNodeTest, DivideStringifyTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    EXPECT_EQ("(x/y)", divide->stringify());
}

TEST(DivideNodeTest, DivideTextTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    EXPECT_EQ("((x)/(y))", divide->text());
}

TEST(DivideNodeTest, DivideExplicitTextTest) {
    auto *divide = new cas::Divide(new cas::Variable('x'), new cas::Variable('y'));
    EXPECT_EQ("div(var(x), var(y))", divide->explicitText());
}
