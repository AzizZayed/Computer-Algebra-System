//
// Created by Abd-El-Aziz Zayed on 2022-09-23.
//

#include "cas/plot/Function.h"
#include "cas/data/ExpressionParser.h"

CAS_NAMESPACE

Function::Function(const std::string& oFormula, cas::Expression* expr, const cas::VarSet& variables)
    : uid(nextId()), expr(expr), variables(variables), originalFormula(oFormula) {}

Function::~Function() {
    delete expr;
}

double Function::evaluate(const cas::VarMap& variables) {
    return expr->evaluate(variables);
}

Function* Function::derivative(char var) {
    return new Function("", expr->derivative(var), this->variables);
}

Function* Function::simplified() {
    return new Function(originalFormula, expr->simplified(), this->variables);
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

const cas::Expression* Function::getExpr() const {
    return expr;
}

const cas::VarSet& Function::getVariables() const {
    return variables;
}

Function Function::parse(const std::string& strFormula) {
    std::string formula = strFormula;

    ExpressionParser& parser = ExpressionParser::getInstance();
    parser.setup(formula);

    if (!parser.isValidExpression(formula)) {
        throw std::invalid_argument("Invalid expression");
    }

    VarSet variables;
    Expression* expr = parser.parse(formula, variables);

    return Function(strFormula, expr, variables);
}

CAS_NAMESPACE_END