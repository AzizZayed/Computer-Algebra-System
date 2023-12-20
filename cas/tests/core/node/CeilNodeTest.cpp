//
// Created by Abd-El-Aziz Zayed on 2022-09-09.
//

#include "cas/node/Ceil.h"
#include "cas/node/Const.h"
#include "gtest/gtest.h"

TEST(CeilNodeTest, CeilCreationTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    EXPECT_EQ(cas::ExpressionType::CEIL, ceil->getProperties().getType());
    EXPECT_EQ("ceiling", ceil->getProperties().getName());
    EXPECT_EQ("ceil", ceil->getProperties().getShortName());
    EXPECT_EQ(nullptr, ceil->getParent());

    auto* pConst = new cas::Const(1);
    EXPECT_TRUE(ceil->getArgument()->equals(pConst));

    delete pConst;
    delete ceil;
}

TEST(CeilNodeTest, CeilDestroyTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    delete ceil;

    EXPECT_NE(ceil, nullptr);
}

TEST(CeilNodeTest, CeilCloneTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    cas::Ceil* ceil2 = ceil->clone();
    EXPECT_EQ(ceil->getProperties().getType(), ceil2->getProperties().getType());
    EXPECT_EQ(ceil->getProperties().getOrder(), ceil2->getProperties().getOrder());
    EXPECT_EQ(ceil->getProperties().getName(), ceil2->getProperties().getName());
    EXPECT_EQ(ceil->getProperties().getShortName(), ceil2->getProperties().getShortName());
    EXPECT_EQ(ceil->getParent(), ceil2->getParent());
    EXPECT_EQ(ceil->getParent(), nullptr);
    EXPECT_TRUE(ceil->getArgument()->equals(ceil2->getArgument()));
    delete ceil2;
    delete ceil;
}

TEST(CeilNodeTest, CeilEvaluationTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    EXPECT_EQ(1, ceil->evaluate({}));

    auto* ceil2 = new cas::Ceil(new cas::Const(-1));
    EXPECT_EQ(-1, ceil2->evaluate({}));

    delete ceil;
    delete ceil2;
}

TEST(CeilNodeTest, CeilEqualsTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    auto* ceil2 = new cas::Ceil(new cas::Const(2));
    auto* ceil3 = new cas::Ceil(new cas::Const(1));
    EXPECT_TRUE(ceil->equals(ceil3));

    EXPECT_FALSE(ceil->equals(ceil2));
    EXPECT_FALSE(ceil2->equals(ceil3));

    delete ceil;
    delete ceil2;
    delete ceil3;
}

TEST(CeilNodeTest, CeilDerivativeTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    EXPECT_THROW({
        try {
            ceil->derivative('x');
        } catch (std::runtime_error& e) {
            EXPECT_STREQ("The ceiling::derivative() operation is not supported", e.what());
            throw;
        } }, std::runtime_error);

    delete ceil;
}

TEST(CeilNodeTest, CeilSimplifiedTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    auto* s = ceil->simplified();
    EXPECT_TRUE(s->equals(new cas::Const(1)));

    delete ceil;
    delete s;
}

TEST(CeilNodeTest, CeilLatexTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    EXPECT_STREQ("\\lceil1\\rceil", ceil->latex().c_str());

    delete ceil;
}

TEST(CeilNodeTest, CeilStringifyTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    EXPECT_STREQ(ceil->stringify().c_str(), L"⌈1⌉");

    delete ceil;
}

TEST(CeilNodeTest, CeilTextTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    EXPECT_STREQ("ceil[1]", ceil->text().c_str());

    delete ceil;
}

TEST(CeilNodeTest, CeilExplicitTextTest) {
    auto* ceil = new cas::Ceil(new cas::Const(1));
    EXPECT_STREQ("ceil(const(1))", ceil->explicitText().c_str());

    delete ceil;
}
