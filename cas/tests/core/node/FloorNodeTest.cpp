//
// Created by Abd-El-Aziz Zayed on 2022-09-09.
//

#include "cas/node/Const.h"
#include "cas/node/Floor.h"
#include "cas/node/Var.h"
#include "gtest/gtest.h"

TEST(FloorNodeTest, FloorCreationTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    EXPECT_EQ(cas::ExpressionType::FLOOR, floor->getProperties().getType());
    EXPECT_EQ("floor_value", floor->getProperties().getName());
    EXPECT_EQ("floor", floor->getProperties().getShortName());
    EXPECT_EQ(nullptr, floor->getParent());

    auto* pConst = new cas::Const(1);
    EXPECT_TRUE(floor->getArgument()->equals(pConst));

    delete pConst;
    delete floor;
}

TEST(FloorNodeTest, FloorDestroyTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    delete floor;

    EXPECT_NE(floor, nullptr);
}

TEST(FloorNodeTest, FloorCloneTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    cas::Floor* floor2 = floor->clone();
    EXPECT_EQ(floor->getProperties().getType(), floor2->getProperties().getType());
    EXPECT_EQ(floor->getProperties().getOrder(), floor2->getProperties().getOrder());
    EXPECT_EQ(floor->getProperties().getName(), floor2->getProperties().getName());
    EXPECT_EQ(floor->getProperties().getShortName(), floor2->getProperties().getShortName());
    EXPECT_EQ(floor->getParent(), floor2->getParent());
    EXPECT_EQ(floor->getParent(), nullptr);
    EXPECT_TRUE(floor->getArgument()->equals(floor2->getArgument()));
    delete floor2;
    delete floor;
}

TEST(FloorNodeTest, FloorEvaluationTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    EXPECT_EQ(1, floor->evaluate({}));

    auto* floor2 = new cas::Floor(new cas::Const(-1));
    EXPECT_EQ(-1, floor2->evaluate({}));

    delete floor;
    delete floor2;
}

TEST(FloorNodeTest, FloorEqualsTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    auto* floor2 = new cas::Floor(new cas::Const(2));
    auto* floor3 = new cas::Floor(new cas::Const(1));
    EXPECT_TRUE(floor->equals(floor3));

    EXPECT_FALSE(floor->equals(floor2));
    EXPECT_FALSE(floor2->equals(floor3));

    delete floor;
    delete floor2;
    delete floor3;
}

TEST(FloorNodeTest, FloorLatexTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    EXPECT_EQ("\\lfloor1\\rfloor", floor->latex());

    auto* floor2 = new cas::Floor(new cas::Const(-1));
    EXPECT_EQ("\\lfloor-1\\rfloor", floor2->latex());

    delete floor;
    delete floor2;
}

TEST(FloorNodeTest, FloorStringifyTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    EXPECT_STREQ(L"⌊1⌋", floor->stringify().c_str());

    auto* floor2 = new cas::Floor(new cas::Const(-1));
    EXPECT_STREQ(L"⌊-1⌋", floor2->stringify().c_str());

    auto* floor3 = new cas::Floor(new cas::Var);
    EXPECT_STREQ(L"⌊x⌋", floor3->stringify().c_str());

    delete floor;
    delete floor2;
}

TEST(FloorNodeTest, FloorSimplifyTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    EXPECT_TRUE(floor->simplified()->equals(floor->getArgument()));

    auto* floor2 = new cas::Floor(new cas::Const(-1));
    EXPECT_TRUE(floor2->simplified()->equals(floor2->getArgument()));

    auto* floor4 = new cas::Floor(new cas::Const(-1.0285));
    auto* sFloor4 = new cas::Const(-2);
    EXPECT_TRUE(floor4->simplified()->equals(sFloor4));

    auto* floor3 = new cas::Floor(new cas::Var);
    EXPECT_TRUE(floor3->simplified()->equals(floor3));

    delete floor;
    delete floor2;
    delete floor3;
    delete floor4;
    delete sFloor4;
}

TEST(FloorNodeTest, FloorDerivativeTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    EXPECT_THROW({
        try {
            floor->derivative('x');
        } catch (std::runtime_error& e) {
            EXPECT_STREQ("The floor_value::derivative() operation is not supported", e.what());
            throw;
        } }, std::runtime_error);
}

TEST(FloorNodeTest, FloorTextTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    EXPECT_EQ("floor[1]", floor->text());

    auto* floor2 = new cas::Floor(new cas::Const(-1));
    EXPECT_EQ("floor[-1]", floor2->text());

    auto* floor3 = new cas::Floor(new cas::Var);
    EXPECT_EQ("floor[x]", floor3->text());

    delete floor;
    delete floor2;
    delete floor3;
}

TEST(FloorNodeTest, FloorExplicitTextTest) {
    auto* floor = new cas::Floor(new cas::Const(1));
    EXPECT_EQ("floor(const(1))", floor->explicitText());

    auto* floor2 = new cas::Floor(new cas::Const(-1));
    EXPECT_EQ("floor(const(-1))", floor2->explicitText());

    auto* floor3 = new cas::Floor(new cas::Var);
    EXPECT_EQ("floor(var(x))", floor3->explicitText());

    delete floor;
    delete floor2;
    delete floor3;
}
