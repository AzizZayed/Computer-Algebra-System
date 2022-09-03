//
// Created by Abd-El-Aziz Zayed on 2022-09-02.
//

#ifndef CAS_LOG_H
#define CAS_LOG_H

#include "core/CAS.h"
#include "Expression.h"

CAS_NAMESPACE

class Log : public Expression {
public:
    explicit Log(Expression* base, Expression* argument)
    : base(base), argument(argument), Expression({ExpressionType::LOGARITHM, "logarithm", "log"})
    {
        base->setParent(this);
        argument->setParent(this);
    }

    Log() = delete;
    ~Log() override
    {
        delete base;
        delete argument;
    }

    double evaluate(const std::unordered_map<char, double>& variables) override;
    bool equals(Expression* expression) override;
    Log* clone() override;
    Expression *derivative(char var) override;
    Expression* simplified() override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string explicitText() override;

private:
    const Expression* base;
    const Expression* argument;
};

CAS_NAMESPACE_END

#endif //CAS_LOG_H
