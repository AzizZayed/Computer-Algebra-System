//
// Created by Abd-El-Aziz Zayed on 2022-09-24.
//

#include "cas/data/ExpressionParser.h"
#include "cas/node/Abs.h"
#include "cas/node/Cbrt.h"
#include "cas/node/Ceil.h"
#include "cas/node/Const.h"
#include "cas/node/Divide.h"
#include "cas/node/Exp.h"
#include "cas/node/Floor.h"
#include "cas/node/Ln.h"
#include "cas/node/Min.h"
#include "cas/node/Mod.h"
#include "cas/node/Negate.h"
#include "cas/node/Power.h"
#include "cas/node/Prod.h"
#include "cas/node/Round.h"
#include "cas/node/Sign.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "cas/node/trig/ArcCos.h"
#include "cas/node/trig/ArcCot.h"
#include "cas/node/trig/ArcCsc.h"
#include "cas/node/trig/ArcSec.h"
#include "cas/node/trig/ArcSin.h"
#include "cas/node/trig/ArcTan.h"
#include "cas/node/trig/Cos.h"
#include "cas/node/trig/Cot.h"
#include "cas/node/trig/Csc.h"
#include "cas/node/trig/Sec.h"
#include "cas/node/trig/Sin.h"
#include "cas/node/trig/Tan.h"
#include "gtest/gtest.h"

TEST(ExpressionParserTest, testSetup) {
    cas::ExpressionParser& parser = cas::ExpressionParser::getInstance();

    std::string str = "(_)(_)-(_)(_)+(_)(_)*(_)(_)/(_)(_)";
    parser.setup(str);
    ASSERT_EQ(str, "(_)*(_)-(_)*(_)+(_)*(_)*(_)*(_)/(_)*(_)");

    str = "Hello World\tHello\nWorld\r";
    parser.setup(str);
    ASSERT_EQ(str, "HelloWorldHelloWorld");

    str = "  ()   {}[]  ((__)()(__)())\n";
    parser.setup(str);
    ASSERT_EQ(str, "((__)*(__))");
}

TEST(ExpressionParserTest, testBalancedBrackets) {
    cas::ExpressionParser& parser = cas::ExpressionParser::getInstance();

    std::string str = "()()()()()()";
    ASSERT_TRUE(parser.balancedBrackets(str));

    str = "(((())))";
    ASSERT_TRUE(parser.balancedBrackets(str));

    str = "(((())))()()()()()";
    ASSERT_TRUE(parser.balancedBrackets(str));

    str = "(((()))";
    ASSERT_FALSE(parser.balancedBrackets(str));

    str = "(((())))()()()()()(";
    ASSERT_FALSE(parser.balancedBrackets(str));

    str = "(()";
    ASSERT_FALSE(parser.balancedBrackets(str));

    str = "((()))))))))";
    ASSERT_FALSE(parser.balancedBrackets(str));
}

TEST(ExpressionParserTest, testGetFirstPairOfNonEmptyBrackets) {
    cas::ExpressionParser& parser = cas::ExpressionParser::getInstance();
    size_t start, end;

    std::string str = "((()))";
    parser.getFirstPairOfNonEmptyBrackets(str, start, end);
    ASSERT_EQ(start, 0);
    ASSERT_EQ(end, 5);

    str = "()";
    parser.getFirstPairOfNonEmptyBrackets(str, start, end);
    ASSERT_EQ(start, 0);
    ASSERT_EQ(end, 0);

    str = "";
    parser.getFirstPairOfNonEmptyBrackets(str, start, end);
    ASSERT_EQ(start, 0);
    ASSERT_EQ(end, 0);

    str = "((()))()()()()()";
    parser.getFirstPairOfNonEmptyBrackets(str, start, end);
    ASSERT_EQ(start, 0);
    ASSERT_EQ(end, 5);

    str = "()()()()()()";
    parser.getFirstPairOfNonEmptyBrackets(str, start, end);
    ASSERT_EQ(start, 0);
    ASSERT_EQ(end, 0);

    str = "(((())))()()()()()";
    parser.getFirstPairOfNonEmptyBrackets(str, start, end);
    ASSERT_EQ(start, 0);
    ASSERT_EQ(end, 7);

    str = "____(+++()+++)";
    parser.getFirstPairOfNonEmptyBrackets(str, start, end);
    ASSERT_EQ(start, 4);
    ASSERT_EQ(end, 13);
}

TEST(ExpressionParserTest, testRemoveUnnecessarySurroundingBrackets) {
    cas::ExpressionParser& parser = cas::ExpressionParser::getInstance();

    std::string str = "((()))";
    parser.removeUnnecessarySurroundingBrackets(str);
    ASSERT_EQ(str, "()");

    str = "(((+)))";
    parser.removeUnnecessarySurroundingBrackets(str);
    ASSERT_EQ(str, "+");

    str = "(((+-)))";
    parser.removeUnnecessarySurroundingBrackets(str);
    ASSERT_EQ(str, "+-");

    str = "((____(+++(+)+++)))";
    parser.removeUnnecessarySurroundingBrackets(str);
    ASSERT_EQ(str, "____(+++(+)+++)");

    str = "-----(+)----";
    parser.removeUnnecessarySurroundingBrackets(str);
    ASSERT_EQ(str, "-----(+)----");

    str = "-----((+))";
    parser.removeUnnecessarySurroundingBrackets(str);
    ASSERT_EQ(str, "-----((+))");
}

TEST(ExpressionParserTest, testParseNoBrackets) {
    cas::ExpressionParser& parser = cas::ExpressionParser::getInstance();
    cas::VarSet vars;

    std::string str = "x";
    cas::Expression* expr = parser.parse(str, vars);
    ASSERT_EQ(expr->text(), "x");
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "x+y";
    expr = parser.parse(str, vars);
    ASSERT_EQ(expr->text(), "((x) + (y))");
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    vars.clear();

    str = "x+y-z";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->add(cas::Var::y()->subtract(cas::Var::z()))));
    ASSERT_EQ(vars.size(), 3);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y', 'z'}));
    vars.clear();

    str = "x*y";
    expr = parser.parse(str, vars);
    ASSERT_EQ(expr->text(), "((x) * (y))");
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    vars.clear();

    str = "x*y*z";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(new cas::Product({cas::Var::x(),
                                               cas::Var::y(),
                                               cas::Var::z()})));
    ASSERT_EQ(vars.size(), 3);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y', 'z'}));
    vars.clear();

    str = "e";
    expr = parser.parse(str, vars);
    ASSERT_EQ(expr->latex(), "e");
    ASSERT_EQ(vars.size(), 0);
    ASSERT_EQ(vars, cas::VarSet{});
    vars.clear();

    str = "pi";
    expr = parser.parse(str, vars);
    ASSERT_EQ(expr->latex(), "\\pi");
    ASSERT_EQ(vars.size(), 0);
    ASSERT_EQ(vars, cas::VarSet{});
    vars.clear();

    str = "phi";
    expr = parser.parse(str, vars);
    ASSERT_EQ(expr->latex(), "\\varphi");
    ASSERT_EQ(vars.size(), 0);
    ASSERT_EQ(vars, cas::VarSet{});
    vars.clear();

    str = "x^2";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->power(2)));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "e^x";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->exp()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "x^2+y^2";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->power(2)->add(cas::Var::y()->power(2))));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    vars.clear();

    str = "x^2+y^2-z^2";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(new cas::Sum({cas::Var::x()->power(2),
                                           cas::Var::y()->power(2)->add(cas::Var::z()->power(2)->negate())})));
    ASSERT_EQ(vars.size(), 3);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y', 'z'}));
    vars.clear();

    str = "x/y";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->divide(cas::Var::y())));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    vars.clear();

    str = "-x/y";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->divide(cas::Var::y())->negate()));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    vars.clear();

    str = "lnx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->ln()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "-lnx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->ln()->negate()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "sinx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->sin()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "cosx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->cos()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "tanx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->tan()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "cotx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->cot()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "secx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->sec()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "cscx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->csc()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "asinx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->asin()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "acosx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->acos()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "atanx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->atan()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "acotx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->acot()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "asecx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->asec()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "acscx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->acsc()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "arcsinx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->asin()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "arccosx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->acos()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "arctanx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->atan()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "arccotx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->acot()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "arcsecx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->asec()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "arccscx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->acsc()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "absx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->abs()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "sqrtx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->sqrt()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "ceilx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->ceil()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "floorx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->floor()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "roundx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->round()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "signx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->sign()));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "logx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->log(10)));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "log2x";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->log(2)));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "logx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->log(10)));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "log3x";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->log(3)));
    ASSERT_EQ(vars.size(), 1);
    ASSERT_EQ(vars, cas::VarSet{'x'});
    vars.clear();

    str = "logbx";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->log(new cas::Var('b'))));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'b'}));
    vars.clear();

    str = "functionx";
    EXPECT_THROW({
        try {
            expr = parser.parse(str, vars);
        } catch (std::invalid_argument& e) {
            ASSERT_STREQ(e.what(), "Invalid expression functionx");
            throw;
        }
    },
                 std::invalid_argument);
    ASSERT_EQ(vars.size(), 0);
    ASSERT_EQ(vars, cas::VarSet{});

    delete expr;
}

TEST(ExpressionParserTest, testParseWithBrackets) {
    cas::ExpressionParser& parser = cas::ExpressionParser::getInstance();
    cas::VarSet vars;

    std::string str = "-cos(x+2*y)";
    cas::Expression* expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->add(cas::Const::n(2)->multiply(cas::Var::y()))->cos()->negate()));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    vars.clear();

    str = "cos(x+2*y)+sin(x+2*y)";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()
                                     ->add(cas::Const::n(2)->multiply(cas::Var::y()))
                                     ->cos()
                                     ->add(cas::Var::x()->add(cas::Const::n(2)->multiply(cas::Var::y()))->sin())));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    vars.clear();

    str = "cos(x)*sin(y)*tan(z)*cot(-w)";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(new cas::Product({cas::Var::x()->cos(),
                                               cas::Var::y()->sin(),
                                               cas::Var::z()->tan(),
                                               cas::Var::w()->negate()->cot()})));
    ASSERT_EQ(vars.size(), 4);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y', 'z', 'w'}));
    vars.clear();

    str = "sqrt(x+y)/abs(x-(y))";
    expr = parser.parse(str, vars);
    cas::Divide* div = cas::Var::x()->add(cas::Var::y())->sqrt()->divide(cas::Var::x()->subtract(cas::Var::y())->abs());
    ASSERT_TRUE(expr->equals(div));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    vars.clear();

    str = "floor(x*y*z*(-w)*s*t*sqrt(x+y-a))^(x+y)";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals((new cas::Product({cas::Var::x(),
                                                cas::Var::y(),
                                                cas::Var::z(),
                                                cas::Var::w()->negate(),
                                                cas::Var::s(),
                                                cas::Var::t(),
                                                cas::Var::x()
                                                        ->add(cas::Var::y()->subtract(cas::Var::var('a')))
                                                        ->sqrt()}))
                                     ->floor()
                                     ->power(cas::Var::x()->add(cas::Var::y()))));
    ASSERT_EQ(vars.size(), 7);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y', 'z', 'w', 't', 's', 'a'}));
    vars.clear();

    str = "x*y*(-z)";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(new cas::Product({cas::Var::x(),
                                               cas::Var::y(),
                                               cas::Var::z()->negate()})));
    ASSERT_EQ(vars.size(), 3);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y', 'z'}));
    vars.clear();

    str = "((x+y)/(a+b))/(z-w)";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()
                                     ->add(cas::Var::y())
                                     ->divide(cas::Var::a()->add(cas::Var::b()))
                                     ->divide(cas::Var::z()->subtract(cas::Var::w()))));
    ASSERT_EQ(vars.size(), 6);
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y', 'a', 'b', 'z', 'w'}));
    vars.clear();

    str = "a*mod(x,y)";
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::a()->multiply(cas::Var::x()->mod(cas::Var::y()))));
    ASSERT_EQ(vars.size(), 3);
    ASSERT_EQ(vars, (cas::VarSet{'a', 'x', 'y'}));
    vars.clear();

    str = "a+b+min(x, y, z, w)";
    parser.setup(str);
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(new cas::Sum({cas::Var::a(),
                                           cas::Var::b(),
                                           new cas::Min({cas::Var::x(),
                                                         cas::Var::y(),
                                                         cas::Var::z(),
                                                         cas::Var::w()})})));
    ASSERT_EQ(vars.size(), 6);
    ASSERT_EQ(vars, (cas::VarSet{'a', 'b', 'x', 'y', 'z', 'w'}));
    vars.clear();

    str = "a*log_a_x";
    parser.setup(str);
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::a()->multiply(cas::Var::x()->log(cas::Var::a()))));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'a', 'x'}));
    vars.clear();

    str = "a*log_(a)_x";
    parser.setup(str);
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::a()->multiply(cas::Var::x()->log(cas::Var::a()))));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'a', 'x'}));
    vars.clear();

    str = "a*log_(a)_(x)";
    parser.setup(str);
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::a()->multiply(cas::Var::x()->log(cas::Var::a()))));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'a', 'x'}));
    vars.clear();

    str = "a*log_a_(x)";
    parser.setup(str);
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::a()->multiply(cas::Var::x()->log(cas::Var::a()))));
    ASSERT_EQ(vars.size(), 2);
    ASSERT_EQ(vars, (cas::VarSet{'a', 'x'}));
    vars.clear();

    str = "e^(x+y)";
    parser.setup(str);
    expr = parser.parse(str, vars);
    ASSERT_TRUE(expr->equals(cas::Var::x()->add(cas::Var::y())->exp()));
    ASSERT_EQ(vars, (cas::VarSet{'x', 'y'}));
    ASSERT_EQ(vars.size(), 2);
    vars.clear();

    delete expr;
}
