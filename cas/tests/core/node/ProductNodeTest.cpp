//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "cas/node/Const.h"
#include "cas/node/Product.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "gtest/gtest.h"

TEST(ProductNodeTest, ProductCreationTest) {
    std::vector<cas::Expression*> expressions = {new cas::Const{1}, new cas::Const{2}, new cas::Const{4}};
    auto product = new cas::Product{expressions};
    EXPECT_EQ(cas::ExpressionType::PRODUCT, product->getProperties().getType());
    EXPECT_EQ("product", product->getProperties().getName());
    EXPECT_EQ("prod", product->getProperties().getShortName());
    EXPECT_EQ('*', product->getSymbol());
    EXPECT_EQ(3, product->getExpressions().size());
    EXPECT_EQ(nullptr, product->getParent());

    for (cas::Expression* exp: expressions) {
        EXPECT_EQ(product, exp->getParent());
    }

    delete product;
}

TEST(ProductNodeTest, ProductDestroyTest) {
    auto product = new cas::Product{{new cas::Const{1}, new cas::Const{2}, new cas::Const{4}}};
    delete product;

    EXPECT_NE(product, nullptr);
}

TEST(ProductNodeTest, ProductCloneTest) {
    auto product = new cas::Product{{new cas::Const{1}, new cas::Const{2}, new cas::Const{4}}};
    cas::Product* product2 = product->clone();
    EXPECT_EQ(product->getProperties().getType(), product2->getProperties().getType());
    EXPECT_EQ(product->getProperties().getName(), product2->getProperties().getName());
    EXPECT_EQ(product->getProperties().getShortName(), product2->getProperties().getShortName());
    EXPECT_EQ(product->getSymbol(), product2->getSymbol());
    EXPECT_EQ(product->getExpressions().size(), product2->getExpressions().size());
    EXPECT_EQ(product->getParent(), product2->getParent());
    EXPECT_EQ(product->getParent(), nullptr);
}

TEST(ProductNodeTest, ProductEvaluationTest) {
    auto product = new cas::Product{{new cas::Var('x'), new cas::Var('y'), new cas::Const{4}}};
    std::unordered_map<char, double> map = {{'x', 3},
                                            {'y', 2}};

    EXPECT_NE(0, product->evaluate(map));
    EXPECT_EQ(24, product->evaluate(map));
}

TEST(ProductNodeTest, ProductEqualsTest) {
    auto* product = new cas::Product{{new cas::Var('x'), new cas::Var('y'), new cas::Const{4}}};
    auto* product2 = new cas::Product{{new cas::Var('x'), new cas::Var('y'), new cas::Const{4}}};
    auto* product3 = new cas::Product{{new cas::Var('x'), new cas::Var('y'), new cas::Const{5}}};
    EXPECT_TRUE(product->equals(product2));
    EXPECT_FALSE(product->equals(product3));

    EXPECT_FALSE(product->equals(new cas::Const(1)));
}

TEST(ProductNodeTest, ProductDerivativeTest) {
    auto* product = new cas::Product{{new cas::Var('x'), new cas::Var('y')}};
    auto* product2 = product->derivative('x');
    auto* product3 = product->derivative('y');

    EXPECT_TRUE(product2->equals(
            new cas::Sum({new cas::Product{
                                  {new cas::Const(1), new cas::Var('y')}},
                          new cas::Product{
                                  {new cas::Var('x'), new cas::Const(0)}}})));

    EXPECT_TRUE(product3->equals(
            new cas::Sum({new cas::Product{
                                  {new cas::Const(0), new cas::Var('y')}},
                          new cas::Product{
                                  {new cas::Var('x'), new cas::Const(1)}}})));
}

TEST(ProductNodeTest, ProductSimplifiedTest) {
    // TODO: implement
}

TEST(ProductNodeTest, ProductLatexTest) {
    auto* product = new cas::Product{
            {
                    new cas::Var('x'),
                    new cas::Var('y'),
                    new cas::Var('w'),
                    new cas::Var('a'),
            }};
    EXPECT_EQ("x * y * w * a", product->latex());
}

TEST(ProductNodeTest, ProductStringifyTest) {
    auto* product2 = new cas::Product{
            {
                    new cas::Var('x'),
                    new cas::Var('y'),
                    new cas::Var('w'),
                    new cas::Var('a'),
            }};
//    EXPECT_EQ("x * y * w * a", product2->stringify());
    EXPECT_TRUE(L"x * y * w * a" == product2->stringify());
}

TEST(ProductNodeTest, ProductTextTest) {
    auto* product = new cas::Product{
            {
                    new cas::Var('x'),
                    new cas::Var('y'),
                    new cas::Var('w'),
                    new cas::Var('a'),
            }};
    EXPECT_EQ("((x) * (y) * (w) * (a))", product->text());
}

TEST(ProductNodeTest, ProductExplicitTextTest) {
    auto* product = new cas::Product{
            {
                    new cas::Var('x'),
                    new cas::Var('y'),
                    new cas::Var('w'),
                    new cas::Var('a'),
            }};
    EXPECT_EQ("prod(var(x), var(y), var(w), var(a))", product->explicitText());
}