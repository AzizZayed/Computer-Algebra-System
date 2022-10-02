#include "cas/node/Const.h"
#include "cas/node/trig/Cos.h"
#include "gtest/gtest.h"

TEST(CosNodeTest, CosCreateTest) {
    auto* pConst = new cas::Const(1);
    auto* cos = new cas::Cos(pConst);
    EXPECT_EQ(cas::ExpressionType::COS, cos->getProperties().getType());
    EXPECT_EQ("cosine", cos->getProperties().getName());
    EXPECT_EQ("cos", cos->getProperties().getShortName());
    EXPECT_EQ(nullptr, cos->getParent());

    EXPECT_TRUE(cos->getArgument()->equals(pConst));
    EXPECT_TRUE(pConst->getParent()->equals(cos));

    delete cos;
}

TEST(CosNodeTest, CosDestroyTest) {
    auto* pConst = new cas::Const(1);
    auto* cos = new cas::Cos(pConst);
    delete cos;

    EXPECT_NE(cos, nullptr);
    EXPECT_NE(pConst, nullptr);
}

TEST(CosNodeTest, CosEvaluateTest) {
    auto* pConst = new cas::Const(1);
    auto* cos = new cas::Cos(pConst);
    EXPECT_EQ(cos->evaluate({}), 0.5403023058681398);

    auto* pConst2 = new cas::Const(0);
    auto* cos2 = new cas::Cos(pConst2);
    EXPECT_EQ(cos2->evaluate({}), 1);

    auto* pConst3 = new cas::Const(-1);
    auto* cos3 = new cas::Cos(pConst3);
    EXPECT_EQ(cos3->evaluate({}), 0.5403023058681398);

    delete cos;
    delete cos2;
    delete cos3;
}

TEST(CosNodeTest, CosEqualsTest) {
}

TEST(CosNodeTest, CosCloneTest) {
}

TEST(CosNodeTest, CosDerivativeTest) {
}

TEST(CosNodeTest, CosSimplifiedTest) {
}

TEST(CosNodeTest, CosLatexTest) {
}

TEST(CosNodeTest, CosStringifyTest) {
}

TEST(CosNodeTest, CosTextTest) {
}

TEST(CosNodeTest, CosExplicitTextTest) {
}
