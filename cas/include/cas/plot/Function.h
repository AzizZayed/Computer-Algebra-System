//
// Created by Abd-El-Aziz Zayed on 2022-09-10.
//

#ifndef CAS_FORMULA_H
#define CAS_FORMULA_H

#include "cas/node/Expression.h"

CAS_NAMESPACE

class Function : public IMath, public IRepresentableMath {
public:
    explicit Function(std::string strFunction, const std::string& name = "z", bool simplify = true);
    virtual ~Function();

    double evaluate(const VarMap& vars) override;
    Function* derivative(char var) override;
    Function* simplifiedDerivative(char var);
    Function* simplified() override;
    bool isEquivalent(IMath* expression) override;

    std::string latex() override;
    std::wstring stringify() override;
    std::string text() override;
    std::string explicitText() override;

    std::string generateFilename() const;

    size_t getUid() const;
    const std::string& getStrExpr() const;
    Expression* getExpr() const;
    const std::string& getName() const;
    const std::string& getFilename() const;
    const VarSet& getVariables() const;

protected:
    explicit Function(const std::string& strFunction, Expression* expr, const VarSet& variables, const std::string& name = "z");

private:
    const size_t uid;
    const std::string strExpr;
    Expression* expr;
    const std::string name;
    const std::string filename;
    VarSet variables;
};

CAS_NAMESPACE_END

#endif//CAS_FORMULA_H
