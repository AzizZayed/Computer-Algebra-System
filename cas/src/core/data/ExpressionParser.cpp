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
#include "cas/node/Max.h"
#include "cas/node/Min.h"
#include "cas/node/Mod.h"
#include "cas/node/Negate.h"
#include "cas/node/Product.h"
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
#include "cas/util/StringUtils.h"

CAS_NAMESPACE

ExpressionParser& ExpressionParser::getInstance() {
    static ExpressionParser instance;
    return instance;
}

void ExpressionParser::setup(std::string& expr) {
    expr.erase(std::remove_if(expr.begin(), expr.end(), isspace), expr.end());// Remove all spaces
    std::replace(expr.begin(), expr.end(), '[', '(');
    std::replace(expr.begin(), expr.end(), ']', ')');
    std::replace(expr.begin(), expr.end(), '{', '(');
    std::replace(expr.begin(), expr.end(), '}', ')');
    replaceAll(expr, "()", "");
    replaceAll(expr, ")(", ")*(");
}

bool ExpressionParser::isValidExpression(const std::string& expr) {
    if (expr.empty()) {
        return false;
    }

    if (!balancedBrackets(expr)) {
        return false;
    }

    return !(contains(expr, "++") || contains(expr, "--") || contains(expr, "**") || contains(expr, "//") || contains(expr, "^^"));
}

bool ExpressionParser::balancedBrackets(const std::string& expr) {
    int count = 0;
    for (char c: expr) {
        if (c == '(') {
            count++;
        } else if (c == ')') {
            count--;
        }
    }
    return count == 0;
}

void ExpressionParser::getFirstPairOfNonEmptyBrackets(std::string expr, size_t& start, size_t& end) {
    start = 0, end = 0;

    replaceAll(expr, "()", "[]");

    int count = 0;
    for (size_t i = 0; i < expr.length(); i++) {
        if (expr[i] == '(') {
            count++;
            if (count == 1) {
                start = i;
            }
        } else if (expr[i] == ')') {
            count--;
            if (count == 0) {
                end = i;
                return;
            }
        }
    }
}

void ExpressionParser::removeUnnecessarySurroundingBrackets(std::string& expr) {
    size_t start, end;
    getFirstPairOfNonEmptyBrackets(expr, start, end);
    while (start != end && start == 0 && end == expr.length() - 1) {
        expr = expr.substr(1, end - 1);
        getFirstPairOfNonEmptyBrackets(expr, start, end);
    }
}

std::string ExpressionParser::pop(std::list<std::string>& list) {
    std::string top = list.front();
    list.pop_front();
    return top;
}

Expression* ExpressionParser::parse(const std::string& expression, VarSet& variables) {
    std::string expr = expression;
    removeUnnecessarySurroundingBrackets(expr);

    if (contains(expr, "(")) {
        size_t start, end;
        getFirstPairOfNonEmptyBrackets(expr, start, end);

        std::string cut = expr;
        std::list<std::string> remove;
        while (start != end) {
            std::string rem = cut.substr(start + 1, end - start - 1);
            remove.push_back(rem);
            replaceOnce(cut, "(" + rem + ")", "()");
            getFirstPairOfNonEmptyBrackets(cut, start, end);
        }

        if (contains(cut, "+")) {
            std::vector<std::string> parts = split(cut, "+");
            for (std::string& part: parts) {
                while (contains(part, "()")) {
                    replaceOnce(part, "()", "(" + pop(remove) + ")");
                }
            }

            std::vector<Expression*> expressions;
            for (const std::string& part: parts) {
                if (!part.empty())
                    expressions.push_back(parse(part, variables));
            }

            return new Sum(expressions);
        } else if (contains(cut, "-")) {
            std::vector<std::string> parts = split(cut, "-");
            for (std::string& part: parts) {
                while (contains(part, "()")) {
                    replaceOnce(part, "()", "(" + pop(remove) + ")");
                }
            }

            if (parts.size() == 2 && parts[0].empty()) {
                return new Negate(parse(parts[1], variables));
            }

            bool first = true;
            std::vector<Expression*> expressions;
            for (const std::string& part: parts) {
                if (!part.empty()) {
                    Expression* neg = parse(part, variables);
                    expressions.push_back(first ? neg : new Negate(neg));
                }
                first = false;
            }

            return new Sum(expressions);
        } else if (contains(cut, "*")) {
            std::vector<std::string> parts = split(cut, "*");
            for (std::string& part: parts) {
                while (contains(part, "()")) {
                    replaceOnce(part, "()", "(" + pop(remove) + ")");
                }
            }

            std::vector<Expression*> expressions;
            for (const std::string& part: parts) {
                if (!part.empty())
                    expressions.push_back(parse(part, variables));
            }

            return new Product(expressions);
        } else if (contains(cut, "/")) {
            std::vector<std::string> parts = splitFirst(cut, "/");

            while (contains(parts[0], "()")) {
                replaceOnce(parts[0], "()", "(" + pop(remove) + ")");
            }
            while (contains(parts[1], "()")) {
                replaceOnce(parts[1], "()", "(" + pop(remove) + ")");
            }

            return new Divide(parse(parts[0], variables), parse(parts[1], variables));
        } else if (contains(cut, "^")) {
            std::vector<std::string> parts = splitFirst(cut, "^");

            while (contains(parts[0], "()")) {
                replaceOnce(parts[0], "()", "(" + pop(remove) + ")");
            }
            while (contains(parts[1], "()")) {
                replaceOnce(parts[1], "()", "(" + pop(remove) + ")");
            }

            std::string& base = parts[0];
            Expression* power = parse(parts[1], variables);
            if (base == "e") {
                return new Exp(power);
            }

            return new Power(parse(base, variables), power);
        } else if (cut == "-()") {
            return new Negate(parse(pop(remove), variables));
        } else if (cut == "sin()") {
            return new Sin(parse(pop(remove), variables));
        } else if (cut == "cos()") {
            return new Cos(parse(pop(remove), variables));
        } else if (cut == "tan()") {
            return new Tan(parse(pop(remove), variables));
        } else if (cut == "cot()") {
            return new Cot(parse(pop(remove), variables));
        } else if (cut == "sec()") {
            return new Sec(parse(pop(remove), variables));
        } else if (cut == "csc()") {
            return new Csc(parse(pop(remove), variables));
        } else if (cut == "asin()" || cut == "arcsin()") {
            return new ArcSin(parse(pop(remove), variables));
        } else if (cut == "acos()" || cut == "arccos()") {
            return new ArcCos(parse(pop(remove), variables));
        } else if (cut == "atan()" || cut == "arctan()") {
            return new ArcTan(parse(pop(remove), variables));
        } else if (cut == "acot()" || cut == "arccot()") {
            return new ArcCot(parse(pop(remove), variables));
        } else if (cut == "asec()" || cut == "arcsec()") {
            return new ArcSec(parse(pop(remove), variables));
        } else if (cut == "acsc()" || cut == "arccsc()") {
            return new ArcCsc(parse(pop(remove), variables));
        } else if (cut == "ln()") {
            return new Ln(parse(pop(remove), variables));
        } else if (cut == "log()") {
            return new Log(parse(pop(remove), variables));
        } else if (cut.starts_with("log_")) {
            std::string log = cut.substr(4);
            std::vector<std::string> parts = split(log, "_");

            while (contains(parts[0], "()")) {
                replaceOnce(parts[0], "()", "(" + pop(remove) + ")");
            }
            while (contains(parts[1], "()")) {
                replaceOnce(parts[1], "()", "(" + pop(remove) + ")");
            }

            return new Log(parse(parts[0], variables), parse(parts[1], variables));
        } else if (cut == "sqrt()") {
            return new Sqrt(parse(pop(remove), variables));
        } else if (cut == "cbrt()") {
            return new Cbrt(parse(pop(remove), variables));
        } else if (cut == "abs()") {
            return new Abs(parse(pop(remove), variables));
        } else if (cut == "exp()") {
            return new Exp(parse(pop(remove), variables));
        } else if (cut == "floor()") {
            return new Floor(parse(pop(remove), variables));
        } else if (cut == "ceil()") {
            return new Ceil(parse(pop(remove), variables));
        } else if (cut == "round()") {
            return new Round(parse(pop(remove), variables));
        } else if (cut == "sign()" || cut == "sgn()") {
            return new Sign(parse(pop(remove), variables));
        } else if (cut == "mod()") {
            std::string mod = pop(remove);
            std::vector<std::string> parts = split(mod, ",");

            if (parts.size() != 2) {
                throw std::invalid_argument("Invalid number of arguments for mod in " + expression);
            }

            return new Mod(parse(parts[0], variables), parse(parts[1], variables));
        } else if (cut == "max()") {
            std::string max = pop(remove);
            std::vector<std::string> parts = split(max, ",");

            std::vector<Expression*> expressions;
            for (const std::string& part: parts) {
                if (!part.empty())
                    expressions.push_back(parse(part, variables));
            }

            return new Max(expressions);
        } else if (cut == "min()") {
            std::string max = pop(remove);
            std::vector<std::string> parts = split(max, ",");

            std::vector<Expression*> expressions;
            for (const std::string& part: parts) {
                if (!part.empty())
                    expressions.push_back(parse(part, variables));
            }

            return new Min(expressions);
        }
    } else if (expr == "e") {
        return cas::Const::E();
    } else if (expr == "pi") {
        return cas::Const::PI();
    } else if (expr == "phi") {
        return cas::Const::PHI();
    } else if (expr.length() == 1 && isalpha(expr[0])) {
        char c = expr[0];
        variables.insert(c);
        return new Var(c);
    } else if (isNumber(expr)) {
        return new Const(std::stod(expr));
    } else if (contains(expr, "+")) {
        std::vector<std::string> parts = split(expr, "+");

        std::vector<Expression*> expressions;
        for (const std::string& part: parts) {
            if (!part.empty())
                expressions.push_back(parse(part, variables));
        }

        return new Sum(expressions);
    } else if (contains(expr, "-")) {
        std::vector<std::string> parts = split(expr, "-");

        if (parts.size() == 2 && parts[0].empty()) {
            return new Negate(parse(parts[1], variables));
        }

        bool first = true;
        std::vector<Expression*> expressions;
        for (const std::string& part: parts) {
            if (!part.empty()) {
                Expression* neg = parse(part, variables);
                expressions.push_back(first ? neg : new Negate(neg));
            }
            first = false;
        }

        return new Sum(expressions);
    } else if (contains(expr, "*")) {
        std::vector<std::string> parts = split(expr, "*");

        std::vector<Expression*> expressions;
        for (const std::string& part: parts) {
            if (!part.empty())
                expressions.push_back(parse(part, variables));
        }

        return new Product(expressions);
    } else if (contains(expr, "/")) {
        std::vector<std::string> parts = splitFirst(expr, "/");
        return new Divide(parse(parts[0], variables), parse(parts[1], variables));
    } else if (contains(expr, "^")) {
        std::vector<std::string> parts = splitFirst(expr, "^");
        std::string& base = parts[0];
        Expression* power = parse(parts[1], variables);

        if (base == "e") {
            return new Exp(power);
        }
        return new Power(parse(base, variables), power);
    } else if (expr.starts_with("-")) {
        return new Negate(parse(expr.substr(1), variables));
    } else if (expr.starts_with("ln")) {
        return new Ln(parse(expr.substr(2), variables));
    } else if (expr.starts_with("sin")) {
        return new Sin(parse(expr.substr(3), variables));
    } else if (expr.starts_with("cos")) {
        return new Cos(parse(expr.substr(3), variables));
    } else if (expr.starts_with("tan")) {
        return new Tan(parse(expr.substr(3), variables));
    } else if (expr.starts_with("cot")) {
        return new Cot(parse(expr.substr(3), variables));
    } else if (expr.starts_with("csc")) {
        return new Csc(parse(expr.substr(3), variables));
    } else if (expr.starts_with("sec")) {
        return new Sec(parse(expr.substr(3), variables));
    } else if (expr.starts_with("asin")) {
        return new ArcSin(parse(expr.substr(4), variables));
    } else if (expr.starts_with("acos")) {
        return new ArcCos(parse(expr.substr(4), variables));
    } else if (expr.starts_with("atan")) {
        return new ArcTan(parse(expr.substr(4), variables));
    } else if (expr.starts_with("acot")) {
        return new ArcCot(parse(expr.substr(4), variables));
    } else if (expr.starts_with("acsc")) {
        return new ArcCsc(parse(expr.substr(4), variables));
    } else if (expr.starts_with("asec")) {
        return new ArcSec(parse(expr.substr(4), variables));
    } else if (expr.starts_with("arcsin")) {
        return new ArcSin(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arccos")) {
        return new ArcCos(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arctan")) {
        return new ArcTan(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arccot")) {
        return new ArcCot(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arccsc")) {
        return new ArcCsc(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arcsec")) {
        return new ArcSec(parse(expr.substr(6), variables));
    } else if (expr.starts_with("abs")) {
        return new Abs(parse(expr.substr(3), variables));
    } else if (expr.starts_with("exp")) {
        return new Exp(parse(expr.substr(3), variables));
    } else if (expr.starts_with("sqrt")) {
        return new Sqrt(parse(expr.substr(4), variables));
    } else if (expr.starts_with("cbrt")) {
        return new Cbrt(parse(expr.substr(4), variables));
    } else if (expr.starts_with("ceil")) {
        return new Ceil(parse(expr.substr(4), variables));
    } else if (expr.starts_with("floor")) {
        return new Floor(parse(expr.substr(5), variables));
    } else if (expr.starts_with("round")) {
        return new Round(parse(expr.substr(5), variables));
    } else if (expr.starts_with("sign")) {
        return new Sign(parse(expr.substr(4), variables));
    } else if (expr.starts_with("sgn")) {
        return new Sign(parse(expr.substr(3), variables));
    } else if (expr.starts_with("log_")) {
        std::string log = expr.substr(4);
        std::vector<std::string> parts = split(log, "_");

        if (parts.size() != 2)
            throw std::invalid_argument("Invalid expression " + expression);

        return new Log(parse(parts[0], variables), parse(parts[1], variables));
    } else if (expr.starts_with("log")) {
        if (expr.length() == 4)
            return new Log(parse(expr.substr(3), variables));
        if (expr.length() == 5)
            return new Log(parse(std::string(1, expr[3]), variables), parse(std::string(1, expr[4]), variables));
        throw std::invalid_argument("Invalid expression " + expression);
    }

    throw std::invalid_argument("Invalid expression " + expression);
}

CAS_NAMESPACE_END