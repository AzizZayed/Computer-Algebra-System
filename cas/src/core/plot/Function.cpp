//
// Created by Abd-El-Aziz Zayed on 2022-09-23.
//

#include "cas/plot/Function.h"
#include "cas/data/ExpressionParser.h"
#include <stdexcept>

CAS_NAMESPACE

Function::Function(std::string strFunction)
    : uid(nextId()), originalFormula(strFunction) {
    ExpressionParser& parser = ExpressionParser::getInstance();

    parser.setup(strFunction);
    if (!parser.isValidExpression(strFunction)) {
        throw std::invalid_argument("Invalid expression");
    }

    this->expr = parser.parse(strFunction, variables);
    this->xDerivative = expr->derivative('x');
    this->yDerivative = expr->derivative('y');
}

Function::Function(const std::string& strFunction, cas::Expression* expr, const cas::VarSet& variables)
    : uid(nextId()), expr(expr), variables(variables), originalFormula(strFunction) {}

Function::~Function() {
    delete expr;
    delete xDerivative;
    delete yDerivative;

    expr = nullptr;
    xDerivative = nullptr;
    yDerivative = nullptr;
}

double Function::evaluate(const cas::VarMap& vars) {
    return expr->evaluate(vars);
}

Function* Function::derivative(char var) {
    return new Function("", expr->derivative(var), this->variables);
}

Function* Function::simplified() {
    return new Function("", expr->simplified(), this->variables);
}

bool Function::isEquivalent(cas::IMath* expression) {
    return expr->isEquivalent(expression);
}

std::string Function::latex() {
    return expr->latex();
}

std::wstring Function::stringify() {
    return expr->stringify();
}

std::string Function::text() {
    return expr->text();
}

std::string Function::explicitText() {
    return expr->explicitText();
}

size_t Function::getUid() const {
    return uid;
}

const std::string& Function::getOriginalFormula() const {
    return originalFormula;
}

Expression* Function::getExpr() const {
    return expr;
}

Expression* Function::getXDerivative() const {
    return xDerivative;
}

Expression* Function::getYDerivative() const {
    return yDerivative;
}

const cas::VarSet& Function::getVariables() const {
    return variables;
}


CAS_NAMESPACE_END
