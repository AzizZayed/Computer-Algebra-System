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
#include "cas/util/StringUtils.h"
#include <algorithm>

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

ExprPtr ExpressionParser::parse(const std::string& expression, VarSet& variables) {
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

            std::vector<ExprPtr> expressions;
            for (const std::string& part: parts) {
                if (!part.empty())
                    expressions.push_back(parse(part, variables));
            }

            return Sum::from(expressions);
        } else if (contains(cut, "-")) {
            std::vector<std::string> parts = split(cut, "-");
            for (std::string& part: parts) {
                while (contains(part, "()")) {
                    replaceOnce(part, "()", "(" + pop(remove) + ")");
                }
            }

            if (parts.size() == 2 && parts[0].empty()) {
                return Negate::from(parse(parts[1], variables));
            }

            bool first = true;
            std::vector<ExprPtr> expressions;
            for (const std::string& part: parts) {
                if (!part.empty()) {
                    ExprPtr neg = parse(part, variables);
                    expressions.push_back(first ? neg : neg->negate());
                }
                first = false;
            }

            return Sum::from(expressions);
        } else if (contains(cut, "*")) {
            std::vector<std::string> parts = split(cut, "*");
            for (std::string& part: parts) {
                while (contains(part, "()")) {
                    replaceOnce(part, "()", "(" + pop(remove) + ")");
                }
            }

            std::vector<ExprPtr> expressions;
            for (const std::string& part: parts) {
                if (!part.empty())
                    expressions.push_back(parse(part, variables));
            }

            return Prod::from(expressions);
        } else if (contains(cut, "/")) {
            std::vector<std::string> parts = splitFirst(cut, "/");

            while (contains(parts[0], "()")) {
                replaceOnce(parts[0], "()", "(" + pop(remove) + ")");
            }
            while (contains(parts[1], "()")) {
                replaceOnce(parts[1], "()", "(" + pop(remove) + ")");
            }

            return Divide::from(parse(parts[0], variables), parse(parts[1], variables));
        } else if (contains(cut, "^")) {
            std::vector<std::string> parts = splitFirst(cut, "^");

            while (contains(parts[0], "()")) {
                replaceOnce(parts[0], "()", "(" + pop(remove) + ")");
            }
            while (contains(parts[1], "()")) {
                replaceOnce(parts[1], "()", "(" + pop(remove) + ")");
            }

            std::string& base = parts[0];
            ExprPtr power = parse(parts[1], variables);
            if (base == "e") {
                return Exp::from(power);
            }

            return Power::from(parse(base, variables), power);
        } else if (cut == "-()") {
            return Negate::from(parse(pop(remove), variables));
        } else if (cut == "sin()") {
            return Sin::from(parse(pop(remove), variables));
        } else if (cut == "cos()") {
            return Cos::from(parse(pop(remove), variables));
        } else if (cut == "tan()") {
            return Tan::from(parse(pop(remove), variables));
        } else if (cut == "cot()") {
            return Cot::from(parse(pop(remove), variables));
        } else if (cut == "sec()") {
            return Sec::from(parse(pop(remove), variables));
        } else if (cut == "csc()") {
            return Csc::from(parse(pop(remove), variables));
        } else if (cut == "asin()" || cut == "arcsin()") {
            return ArcSin::from(parse(pop(remove), variables));
        } else if (cut == "acos()" || cut == "arccos()") {
            return ArcCos::from(parse(pop(remove), variables));
        } else if (cut == "atan()" || cut == "arctan()") {
            return ArcTan::from(parse(pop(remove), variables));
        } else if (cut == "acot()" || cut == "arccot()") {
            return ArcCot::from(parse(pop(remove), variables));
        } else if (cut == "asec()" || cut == "arcsec()") {
            return ArcSec::from(parse(pop(remove), variables));
        } else if (cut == "acsc()" || cut == "arccsc()") {
            return ArcCsc::from(parse(pop(remove), variables));
        } else if (cut == "ln()") {
            return Ln::from(parse(pop(remove), variables));
        } else if (cut == "log()") {
            return Log::from(parse(pop(remove), variables));
        } else if (cut.starts_with("log_")) {
            std::string log = cut.substr(4);
            std::vector<std::string> parts = split(log, "_");

            while (contains(parts[0], "()")) {
                replaceOnce(parts[0], "()", "(" + pop(remove) + ")");
            }
            while (contains(parts[1], "()")) {
                replaceOnce(parts[1], "()", "(" + pop(remove) + ")");
            }

            return Log::from(parse(parts[0], variables), parse(parts[1], variables));
        } else if (cut == "sqrt()") {
            return Sqrt::from(parse(pop(remove), variables));
        } else if (cut == "cbrt()") {
            return Cbrt::from(parse(pop(remove), variables));
        } else if (cut == "abs()") {
            return Abs::from(parse(pop(remove), variables));
        } else if (cut == "exp()") {
            return Exp::from(parse(pop(remove), variables));
        } else if (cut == "floor()") {
            return Floor::from(parse(pop(remove), variables));
        } else if (cut == "ceil()") {
            return Ceil::from(parse(pop(remove), variables));
        } else if (cut == "round()") {
            return Round::from(parse(pop(remove), variables));
        } else if (cut == "sign()" || cut == "sgn()") {
            return Sign::from(parse(pop(remove), variables));
        } else if (cut == "mod()") {
            std::string mod = pop(remove);
            std::vector<std::string> parts = split(mod, ",");

            if (parts.size() != 2) {
                throw std::invalid_argument("Invalid number of arguments for mod in " + expression);
            }

            return Mod::from(parse(parts[0], variables), parse(parts[1], variables));
        } else if (cut == "max()") {
            std::string max = pop(remove);
            std::vector<std::string> parts = split(max, ",");

            std::vector<ExprPtr> expressions;
            for (const std::string& part: parts) {
                if (!part.empty())
                    expressions.push_back(parse(part, variables));
            }

            return Max::from(expressions);
        } else if (cut == "min()") {
            std::string max = pop(remove);
            std::vector<std::string> parts = split(max, ",");

            std::vector<ExprPtr> expressions;
            for (const std::string& part: parts) {
                if (!part.empty())
                    expressions.push_back(parse(part, variables));
            }

            return Min::from(expressions);
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
        return Var::from(c);
    } else if (isNumber(expr)) {
        return Const::from(std::stod(expr));
    } else if (contains(expr, "+")) {
        std::vector<std::string> parts = split(expr, "+");

        std::vector<ExprPtr> expressions;
        for (const std::string& part: parts) {
            if (!part.empty())
                expressions.push_back(parse(part, variables));
        }

        return Sum::from(expressions);
    } else if (contains(expr, "-")) {
        std::vector<std::string> parts = split(expr, "-");

        if (parts.size() == 2 && parts[0].empty()) {
            return Negate::from(parse(parts[1], variables));
        }

        bool first = true;
        std::vector<ExprPtr> expressions;
        for (const std::string& part: parts) {
            if (!part.empty()) {
                ExprPtr neg = parse(part, variables);
                expressions.push_back(first ? neg : Negate::from(neg));
            }
            first = false;
        }

        return Sum::from(expressions);
    } else if (contains(expr, "*")) {
        std::vector<std::string> parts = split(expr, "*");

        std::vector<ExprPtr> expressions;
        for (const std::string& part: parts) {
            if (!part.empty())
                expressions.push_back(parse(part, variables));
        }

        return Prod::from(expressions);
    } else if (contains(expr, "/")) {
        std::vector<std::string> parts = splitFirst(expr, "/");
        return Divide::from(parse(parts[0], variables), parse(parts[1], variables));
    } else if (contains(expr, "^")) {
        std::vector<std::string> parts = splitFirst(expr, "^");
        std::string& base = parts[0];
        ExprPtr power = parse(parts[1], variables);

        if (base == "e") {
            return Exp::from(power);
        }
        return Power::from(parse(base, variables), power);
    } else if (expr.starts_with("-")) {
        return Negate::from(parse(expr.substr(1), variables));
    } else if (expr.starts_with("ln")) {
        return Ln::from(parse(expr.substr(2), variables));
    } else if (expr.starts_with("sin")) {
        return Sin::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("cos")) {
        return Cos::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("tan")) {
        return Tan::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("cot")) {
        return Cot::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("csc")) {
        return Csc::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("sec")) {
        return Sec::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("asin")) {
        return ArcSin::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("acos")) {
        return ArcCos::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("atan")) {
        return ArcTan::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("acot")) {
        return ArcCot::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("acsc")) {
        return ArcCsc::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("asec")) {
        return ArcSec::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("arcsin")) {
        return ArcSin::from(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arccos")) {
        return ArcCos::from(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arctan")) {
        return ArcTan::from(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arccot")) {
        return ArcCot::from(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arccsc")) {
        return ArcCsc::from(parse(expr.substr(6), variables));
    } else if (expr.starts_with("arcsec")) {
        return ArcSec::from(parse(expr.substr(6), variables));
    } else if (expr.starts_with("abs")) {
        return Abs::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("exp")) {
        return Exp::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("sqrt")) {
        return Sqrt::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("cbrt")) {
        return Cbrt::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("ceil")) {
        return Ceil::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("floor")) {
        return Floor::from(parse(expr.substr(5), variables));
    } else if (expr.starts_with("round")) {
        return Round::from(parse(expr.substr(5), variables));
    } else if (expr.starts_with("sign")) {
        return Sign::from(parse(expr.substr(4), variables));
    } else if (expr.starts_with("sgn")) {
        return Sign::from(parse(expr.substr(3), variables));
    } else if (expr.starts_with("log_")) {
        std::string log = expr.substr(4);
        std::vector<std::string> parts = split(log, "_");

        if (parts.size() != 2)
            throw std::invalid_argument("Invalid expression " + expression);

        return Log::from(parse(parts[0], variables), parse(parts[1], variables));
    } else if (expr.starts_with("log")) {
        if (expr.length() == 4)
            return Log::from(parse(expr.substr(3), variables));
        if (expr.length() == 5)
            return Log::from(parse(std::string(1, expr[3]), variables), parse(std::string(1, expr[4]), variables));
        throw std::invalid_argument("Invalid expression " + expression);
    }

    throw std::invalid_argument("Invalid expression " + expression);
}

CAS_NAMESPACE_END