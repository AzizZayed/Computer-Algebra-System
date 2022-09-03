//
// Created by Abd-El-Aziz Zayed on 2022-09-01.
//

#include "gtest/gtest.h"
#include "core/CAS.h"
#include "core/node/Product.h"
#include "core/node/Constant.h"
#include "core/node/Variable.h"
#include "core/node/Sum.h"

TEST(ProductNodeTest, ProductCreationTest) {
    auto product = new cas::Product{{new cas::Constant{1}, new cas::Constant{2}, new cas::Constant{4}}};
    EXPECT_EQ(cas::ExpressionType::PRODUCT, product->getProperties().getType());
    EXPECT_EQ("product", product->getProperties().getName());
    EXPECT_EQ("prod", product->getProperties().getShortName());
    EXPECT_EQ('*', product->getSymbol());
    EXPECT_EQ(3, product->getExpressions().size());
    EXPECT_EQ(nullptr, product->getParent());
}

TEST(ProductNodeTest, ProductDestroyTest) {
    auto product = new cas::Product{{new cas::Constant{1}, new cas::Constant{2}, new cas::Constant{4}}};
    delete product;

    EXPECT_NE(product, nullptr);
}

TEST(ProductNodeTest, ProductCloneTest) {
    auto product = new cas::Product{{new cas::Constant{1}, new cas::Constant{2}, new cas::Constant{4}}};
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
    auto product = new cas::Product{{new cas::Variable('x'), new cas::Variable('y'), new cas::Constant{4}}};
    std::unordered_map<char, double> map = {{'x', 3}, {'y', 2}};

    EXPECT_NE(0, product->evaluate(map));
    EXPECT_EQ(24, product->evaluate(map));
}

TEST(ProductNodeTest, ProductEqualsTest) {
    auto* product = new cas::Product{{new cas::Variable('x'), new cas::Variable('y'), new cas::Constant{4}}};
    auto* product2 = new cas::Product{{new cas::Variable('x'), new cas::Variable('y'), new cas::Constant{4}}};
    auto* product3 = new cas::Product{{new cas::Variable('x'), new cas::Variable('y'), new cas::Constant{5}}};
    EXPECT_TRUE(product->equals(product2));
    EXPECT_FALSE(product->equals(product3));

    EXPECT_FALSE(product->equals(new cas::Constant(1)));
}

TEST(ProductNodeTest, ProductDerivativeTest) {
    auto* product = new cas::Product{{new cas::Variable('x'), new cas::Variable('y')}};
    auto* product2 = product->derivative('x');
    auto* product3 = product->derivative('y');

    EXPECT_TRUE(product2->equals(
            new cas::Sum({
                new cas::Product{
                    {new cas::Constant(1), new cas::Variable('y')}
                    },
                new cas::Product{
                    {new cas::Variable('x'), new cas::Constant(0)}
                }
            })));

    EXPECT_TRUE(product3->equals(
            new cas::Sum({
                new cas::Product{
                    {new cas::Constant(0), new cas::Variable('y')}
                },
                new cas::Product{
                    {new cas::Variable('x'), new cas::Constant(1)}
                }
            })));
}

TEST(ProductNodeTest, ProductSimplifiedTest) {
    // TODO: implement
}

TEST(ProductNodeTest, ProductLatexTest) {
    auto* product = new cas::Product{
        {
            new cas::Variable('x'),
            new cas::Variable('y'),
            new cas::Variable('w'),
            new cas::Variable('a'),
        }
    };
    EXPECT_EQ("x * y * w * a", product->latex());
}

TEST(ProductNodeTest, ProductStringifyTest) {
    auto* product2 = new cas::Product{
            {
                    new cas::Variable('x'),
                    new cas::Variable('y'),
                    new cas::Variable('w'),
                    new cas::Variable('a'),
            }
    };
    EXPECT_EQ("x * y * w * a", product2->stringify());
}

TEST(ProductNodeTest, ProductTextTest) {
    auto* product = new cas::Product{
            {
                    new cas::Variable('x'),
                    new cas::Variable('y'),
                    new cas::Variable('w'),
                    new cas::Variable('a'),
            }
    };
    EXPECT_EQ("((x) * (y) * (w) * (a))", product->text());
}

TEST(ProductNodeTest, ProductFullTextTest) {
    auto* product = new cas::Product{
            {
                    new cas::Variable('x'),
                    new cas::Variable('y'),
                    new cas::Variable('w'),
                    new cas::Variable('a'),
            }
    };
    EXPECT_EQ("prod(x, y, w, a)", product->explicitText());
}