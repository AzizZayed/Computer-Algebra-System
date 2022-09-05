//
// Created by Abd-El-Aziz Zayed on 2022-09-04.
//

#ifndef CAS_MULTIPLEINPUTFUNCTION_H
#define CAS_MULTIPLEINPUTFUNCTION_H

#include "core/CAS.h"
#include "Expression.h"
#include <vector>

CAS_NAMESPACE

class MultipleInputFunction : public Expression {
public:
    MultipleInputFunction() = delete;
    ~MultipleInputFunction() override;

    bool equals(Expression* expression) override;

    std::string latex() override;
    std::string stringify() override;
    std::string text() override;
    std::string explicitText() override;

    std::vector<Expression*> getExpressions() const { return {expressions}; }

protected:
    explicit MultipleInputFunction(const ExpressionProperties& props, std::vector<Expression*> expressions);

protected:
    std::vector<Expression*> expressions;
};

CAS_NAMESPACE_END

#endif //CAS_MULTIPLEINPUTFUNCTION_H
