//
// Created by Abd-El-Aziz Zayed on 2022-09-08.
//

#include "cas/node/Abs.h"
#include "cas/node/Const.h"
#include "cas/node/Var.h"
#include "gtest/gtest.h"

TEST(AbsNodeTest, AbsCreationTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    EXPECT_EQ(cas::ExpressionType::ABSOLUTE_VALUE, abs->getProperties().getType());
    EXPECT_EQ("absolute_value", abs->getProperties().getName());
    EXPECT_EQ("abs", abs->getProperties().getShortName());
    EXPECT_EQ(nullptr, abs->getParent());

    auto* pConst = new cas::Const(1);
    EXPECT_TRUE(abs->getArgument()->equals(pConst));

    delete pConst;
    delete abs;
}

TEST(AbsNodeTest, AbsDestroyTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    delete abs;

    EXPECT_NE(abs, nullptr);
}

TEST(AbsNodeTest, AbsCloneTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    cas::Abs* abs2 = abs->clone();
    EXPECT_EQ(abs->getProperties().getType(), abs2->getProperties().getType());
    EXPECT_EQ(abs->getProperties().getOrder(), abs2->getProperties().getOrder());
    EXPECT_EQ(abs->getProperties().getName(), abs2->getProperties().getName());
    EXPECT_EQ(abs->getProperties().getShortName(), abs2->getProperties().getShortName());
    EXPECT_EQ(abs->getParent(), abs2->getParent());
    EXPECT_EQ(abs->getParent(), nullptr);
    EXPECT_TRUE(abs->getArgument()->equals(abs2->getArgument()));
    delete abs2;
    delete abs;
}

TEST(AbsNodeTest, AbsEvaluationTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    EXPECT_EQ(1, abs->evaluate({}));

    auto* abs2 = new cas::Abs(new cas::Const(-1));
    EXPECT_EQ(1, abs2->evaluate({}));

    delete abs;
    delete abs2;
}

TEST(AbsNodeTest, AbsEqualsTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    auto* abs2 = new cas::Abs(new cas::Const(2));
    auto* abs3 = new cas::Abs(new cas::Const(1));
    EXPECT_TRUE(abs->equals(abs3));
    EXPECT_TRUE(abs->equals(abs));
    EXPECT_FALSE(abs->equals(abs2));

    EXPECT_FALSE(abs3->equals(abs2));

    auto* var = new cas::Var('x');
    EXPECT_FALSE(abs->equals(var));

    delete abs;
    delete abs2;
    delete abs3;
}

TEST(AbsNodeTest, AbsDerivativeTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    EXPECT_THROW({
        try {
            abs->derivative('x');
        } catch (std::runtime_error& e) {
            EXPECT_STREQ("The absolute_value::derivative() operation is not supported", e.what());
            throw;
        } }, std::runtime_error);
}

TEST(AbsNodeTest, AbsSimplifiedTest) {
    auto* pConst = new cas::Const(1);
    auto* abs = new cas::Abs(pConst);
    EXPECT_TRUE(abs->simplified()->equals(pConst));

    auto* abs2 = new cas::Abs(new cas::Const(-1));
    EXPECT_TRUE(abs2->simplified()->equals(new cas::Const(1)));

    auto* abs3 = new cas::Abs(new cas::Var('x'));
    EXPECT_TRUE(abs3->simplified()->equals(abs3));

    delete abs;
    delete abs2;
}

TEST(AbsNodeTest, AbsLatexTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    EXPECT_STREQ("\\left|1\\right|", abs->latex().c_str());

    auto* abs2 = new cas::Abs(new cas::Const(-1));
    EXPECT_STREQ("\\left|-1\\right|", abs2->latex().c_str());

    auto* abs3 = new cas::Abs(new cas::Var);
    EXPECT_STREQ("\\left|x\\right|", abs3->latex().c_str());

    delete abs;
    delete abs2;
    delete abs3;
}

TEST(AbsNodeTest, AbsStringifyTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    EXPECT_STREQ(L"|1|", abs->stringify().c_str());

    auto* abs2 = new cas::Abs(new cas::Const(-1));
    EXPECT_STREQ(L"|-1|", abs2->stringify().c_str());

    auto* abs3 = new cas::Abs(new cas::Var);
    EXPECT_STREQ(L"|x|", abs3->stringify().c_str());

    delete abs;
    delete abs2;
    delete abs3;
}

TEST(AbsNodeTest, AbsTextTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    EXPECT_STREQ("|1|", abs->text().c_str());

    auto* abs2 = new cas::Abs(new cas::Const(-1));
    EXPECT_STREQ("|-1|", abs2->text().c_str());

    auto* abs3 = new cas::Abs(new cas::Var);
    EXPECT_STREQ("|x|", abs3->text().c_str());

    delete abs;
    delete abs2;
    delete abs3;
}

TEST(AbsNodeTest, AbsExplicitTextTest) {
    auto* abs = new cas::Abs(new cas::Const(1));
    EXPECT_STREQ("abs(const(1))", abs->explicitText().c_str());

    auto* abs2 = new cas::Abs(new cas::Const(-1));
    EXPECT_STREQ("abs(const(-1))", abs2->explicitText().c_str());

    auto* abs3 = new cas::Abs(new cas::Var);
    EXPECT_STREQ("abs(var(x))", abs3->explicitText().c_str());

    delete abs;
    delete abs2;
    delete abs3;
}