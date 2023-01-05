//
// Created by Abd-El-Aziz Zayed on 2022-09-09.
//

#include "cas/node/Const.h"
#include "cas/node/Exp.h"
#include "cas/node/Prod.h"
#include "cas/node/Var.h"
#include "gtest/gtest.h"

TEST(ExpNodeTest, ExpCreationTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    EXPECT_EQ(cas::ExpressionType::EXPONENTIAL, exp->getProperties().getType());
    EXPECT_EQ("exponential", exp->getProperties().getName());
    EXPECT_EQ("exp", exp->getProperties().getShortName());
    EXPECT_EQ(nullptr, exp->getParent());

    auto* pConst = new cas::Const(1);
    cas::Const* e = cas::Const::E();
    EXPECT_TRUE(exp->getBase()->equals(e));
    EXPECT_TRUE(exp->getExponent()->equals(pConst));

    delete e;
    delete pConst;
    delete exp;
}

TEST(ExpNodeTest, ExpDestroyTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    delete exp;

    EXPECT_NE(exp, nullptr);
}

TEST(ExpNodeTest, ExpCloneTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    cas::Exp* exp2 = exp->clone();
    EXPECT_EQ(exp->getProperties().getType(), exp2->getProperties().getType());
    EXPECT_EQ(exp->getProperties().getOrder(), exp2->getProperties().getOrder());
    EXPECT_EQ(exp->getProperties().getName(), exp2->getProperties().getName());
    EXPECT_EQ(exp->getProperties().getShortName(), exp2->getProperties().getShortName());
    EXPECT_EQ(exp->getParent(), exp2->getParent());
    EXPECT_EQ(exp->getParent(), nullptr);
    EXPECT_TRUE(exp->getBase()->equals(exp2->getBase()));
    delete exp2;
    delete exp;
}

TEST(ExpNodeTest, ExpEvaluationTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    EXPECT_EQ(cas::math::E, exp->evaluate({}));

    auto* exp2 = new cas::Exp(new cas::Const(-1));
    EXPECT_EQ(1.0 / cas::math::E, exp2->evaluate({}));

    delete exp;
    delete exp2;
}

TEST(ExpNodeTest, ExpEqualsTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    auto* exp2 = new cas::Exp(new cas::Const(2));
    auto* exp3 = new cas::Exp(new cas::Const(1));
    EXPECT_TRUE(exp->equals(exp3));

    EXPECT_FALSE(exp->equals(exp2));
    EXPECT_FALSE(exp2->equals(exp3));

    delete exp;
    delete exp2;
    delete exp3;
}

TEST(ExpNodeTest, ExpLatexTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    EXPECT_EQ("e^{1}", exp->latex());

    auto* exp2 = new cas::Exp(new cas::Const(-1));
    EXPECT_EQ("e^{-1}", exp2->latex());

    delete exp;
    delete exp2;
}

TEST(ExpNodeTest, ExpDerivativeTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    auto* dExp = exp->derivative('x');
    EXPECT_TRUE(dExp->equals(new cas::Const(0)));

    auto* exp2 = new cas::Exp(new cas::Var);
    auto* dExp2 = exp2->derivative('x');
    auto* der = new cas::Product({exp2->clone(), new cas::Const(1)});
    EXPECT_TRUE(dExp2->equals(der));

    delete exp;
    delete exp2;
    delete dExp;
    delete dExp2;
}

TEST(ExpNodeTest, ExpSimplifyTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    auto* sExp = exp->simplified();
    EXPECT_TRUE(sExp->equals(new cas::Const(cas::math::E)));

    auto* exp2 = new cas::Exp(new cas::Const(-1));
    auto* sExp2 = exp2->simplified();
    EXPECT_TRUE(sExp2->equals(exp2));

    delete exp;
    delete exp2;
    delete sExp;
    delete sExp2;
}

TEST(ExpNodeTest, ExpStringifyTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    EXPECT_EQ(L"e^1", exp->stringify());

    auto* exp2 = new cas::Exp(new cas::Const(-1));
    EXPECT_EQ(L"e^-1", exp2->stringify());

    delete exp;
    delete exp2;
}

TEST(ExpNodeTest, ExpTextTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    EXPECT_EQ("(2.718282)^(1)", exp->text());

    auto* exp2 = new cas::Exp(new cas::Const(-1));
    EXPECT_EQ("(2.718282)^(-1)", exp2->text());

    delete exp;
    delete exp2;
}

TEST(ExpNodeTest, ExpExplicitTest) {
    auto* exp = new cas::Exp(new cas::Const(1));
    EXPECT_EQ("exp(const(1))", exp->explicitText());

    auto* exp2 = new cas::Exp(new cas::Const(-1));
    EXPECT_EQ("exp(const(-1))", exp2->explicitText());

    delete exp;
    delete exp2;
}
