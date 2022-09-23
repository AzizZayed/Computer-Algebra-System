//
// Created by Abd-El-Aziz Zayed on 2022-09-10.
//

#ifndef CAS_FORMULA_H
#define CAS_FORMULA_H

#include "cas/CAS.h"
#include "cas/node/Expression.h"

CAS_NAMESPACE

class Formula : public IMath, public IRepresentableMath {
public:
    static Formula parse(const std::string& strFormula);

    double evaluate(const VarMap& variables) override;
    IMath* derivative(char var) override;
    IMath* simplified() override;
    bool isEquivalent(IMath* expr) override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;

protected:
    explicit Formula(Expression* expr, const VarMap& variables);

private:
    Expression* expr;
    VarMap variables;
    std::string originalFormula;
};

CAS_NAMESPACE_END

#endif//CAS_FORMULA_H
