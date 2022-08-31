//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_VARIABLE_H
#define CAS_VARIABLE_H

#include "core/CAS.h"
#include "Expression.h"
#include "Constant.h"

CAS_NAMESPACE

class Variable : public Expression {
public:
    explicit Variable(Expression* parent, char variable);
    explicit Variable(char variable) : Variable(nullptr, variable) {}
    explicit Variable(Expression* parent) : Variable(parent, VAR_X) {}
    explicit Variable() : Variable(nullptr) {}
    ~Variable() override;

    char getSymbol() const { return symbol; }

    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(Expression* expression) override;

    Variable* clone(Expression* newParent) override;
    Variable* clone() override { return clone(nullptr); }

    Constant* derivative(Expression* newParent, char var) override;
    Variable* simplified(Expression* newParent) override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string fullText() override;
private:
    const char symbol;

public:
    static const char VAR_X = 'x';
};

CAS_NAMESPACE_END

#endif //CAS_VARIABLE_H
