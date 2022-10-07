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
    explicit Function(std::string strFunction);
    static Function parse(std::string strFunction);
    virtual ~Function();

    double evaluate(const VarMap& vars) override;
    Function* derivative(char var) override;
    Function* simplified() override;
    bool isEquivalent(IMath* expression) override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;

    size_t getUid() const;
    const std::string& getOriginalFormula() const;
    Expression* getExpr() const;
    const VarSet& getVariables() const;

protected:
    explicit Function(const std::string& oFormula, Expression* expr, const VarSet& variables);

private:
    const size_t uid;
    Expression* expr;
    VarSet variables;
    std::string originalFormula;
};

CAS_NAMESPACE_END

#endif//CAS_FORMULA_H
