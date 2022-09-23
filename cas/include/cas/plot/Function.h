//
// Created by Abd-El-Aziz Zayed on 2022-09-10.
//

#ifndef CAS_FORMULA_H
#define CAS_FORMULA_H

#include "cas/CAS.h"
#include "cas/node/Expression.h"

CAS_NAMESPACE

class Function : public IMath, public IRepresentableMath {
public:
    static Function parse(const std::string& strFormula);

    double evaluate(const VarMap& variables) override;
    Function* derivative(char var) override;
    Function* simplified() override;
    bool isEquivalent(IMath* expr) override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;

protected:
    explicit Function(Expression* expr, const VarMap& variables);

private:
    const size_t id;
    Expression* expr;
    VarMap variables;
    std::string originalFormula;
};

CAS_NAMESPACE_END

#endif//CAS_FORMULA_H
