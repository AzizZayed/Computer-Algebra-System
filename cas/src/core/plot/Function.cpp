//
// Created by Abd-El-Aziz Zayed on 2022-09-23.
//

#include "cas/plot/Function.h"
#include "cas/data/ExpressionParser.h"
#include <stdexcept>

CAS_NAMESPACE

Function::Function(std::string strFunction, const std::string& name)
    : uid(nextId()), strExpr(strFunction), name(name), filename(generateFilename())
{
    ExpressionParser& parser = ExpressionParser::getInstance();

    parser.setup(strFunction);
    if (!parser.isValidExpression(strFunction)) {
        throw std::invalid_argument("Invalid expression");
    }

    this->expr = parser.parse(strFunction, variables);
}

Function::Function(const std::string& strFunction, cas::Expression* expr, const cas::VarSet& variables, const std::string& name)
    : uid(nextId()), strExpr(strFunction), expr(expr), name(name), filename(generateFilename()), variables(variables) {}

Function::~Function() {
    delete expr;
}

double Function::evaluate(const cas::VarMap& vars) {
    return expr->evaluate(vars);
}

Function* Function::derivative(char var) {
    Expression* pExpression = expr->derivative(var);
    return new Function(pExpression->text(), pExpression, this->variables, this->name + "_" + var);
}

Function* Function::simplified() {
    Expression* pExpression = expr->simplified();
    return new Function(pExpression->text(), pExpression, this->variables, this->name + "_s");
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

std::string Function::generateFilename() const {
    return "f_" + std::to_string(uid);
}

size_t Function::getUid() const {
    return uid;
}

const std::string& Function::getStrExpr() const {
    return strExpr;
}

Expression* Function::getExpr() const {
    return expr;
}

const std::string& Function::getName() const {
    return name;
}

const std::string& Function::getFilename() const {
    return filename;
}

const cas::VarSet& Function::getVariables() const {
    return variables;
}


CAS_NAMESPACE_END
