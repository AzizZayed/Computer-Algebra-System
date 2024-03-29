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

    double evaluate(const VariableMap& vars) override;
    Function* derivative(char var) override;
    Function* simplifiedDerivative(char var);
    Function* simplified() override;
    bool equivalent(IMath* expression) override;

    std::string latex() override;
    std::string str() override;
    std::string text() override;
    std::string explicitText() override;

    [[nodiscard]] std::string generateFilename() const;

    [[nodiscard]] size_t getUid() const;
    [[nodiscard]] const std::string& getStrExpr() const;
    [[nodiscard]] Expression* getExpr() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getFilename() const;
    [[nodiscard]] const VarSet& getVariables() const;

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

#endif  //CAS_FORMULA_H
