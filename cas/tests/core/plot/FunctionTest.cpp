//
// Created by Abd-El-Aziz Zayed on 2022-10-06.
//

#include "cas/plot/Function.h"
#include "cas/node/Const.h"
#include "cas/node/Power.h"
#include "cas/node/Product.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "gtest/gtest.h"
#include <vector>

TEST(FunctionTest, FunctionTestCreate) {
    const char* str = "x^2 + 2*x + 1";
    cas::Function f(str);
    EXPECT_EQ(f.getUid(), 1);
    EXPECT_EQ(f.getStrExpr(), str);
    EXPECT_EQ(f.getVariables().size(), 1);
    EXPECT_EQ(f.getVariables(), cas::VarSet {'x'});

    EXPECT_TRUE(f.getExpr()->equals(
            new cas::Sum({cas::Var::x()->power(2),
                          cas::Const::n(2)->multiply(cas::Var::x()),
                          cas::Const::n(1)})));

    EXPECT_EQ(f.getExpr()->getProperties().getType(), cas::ExpressionType::SUM);
    EXPECT_EQ(f.getExpr()->getProperties().getName(), "summation");
    EXPECT_EQ(f.getExpr()->getProperties().getShortName(), "sum");

    auto* sum = dynamic_cast<cas::Sum*>(f.getExpr());
    EXPECT_EQ(sum->getSymbol(), '+');
    EXPECT_EQ(sum->getExpressions().size(), 3);
    EXPECT_EQ(sum->getParent(), nullptr);
}