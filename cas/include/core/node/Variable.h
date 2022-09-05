//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_VARIABLE_H
#define CAS_VARIABLE_H

#include "Constant.h"
#include "Expression.h"
#include "core/CAS.h"
#include <string>

CAS_NAMESPACE

class Variable : public Expression {
public:
    explicit Variable(char variable);

    explicit Variable() : Variable(VAR_X) {}

    ~Variable() override;

    double evaluate(const std::unordered_map<char, double>& variables) override;

    bool equals(Expression* expression) override;

    Variable* clone() override;

    Constant* derivative(char var) override;

    Variable* simplified() override;

    std::string latex() override;

    std::string stringify() override;

    std::string text() override;

    char getSymbol() const { return symbol; }

private:
    const char symbol;

public:
    static const char VAR_X = 'x';
};

CAS_NAMESPACE_END

#endif//CAS_VARIABLE_H
