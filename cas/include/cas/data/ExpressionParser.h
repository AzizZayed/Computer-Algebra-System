#ifndef CAS_EXPRESSIONPARSER_H
#define CAS_EXPRESSIONPARSER_H

#include "cas/node/Expression.h"
#include <list>

CAS_NAMESPACE

class ExpressionParser {
public:
    static ExpressionParser& getInstance();
    Expression* parse(const std::string& expression, VarSet& variables);

    void setup(std::string& expr);
    bool isValidExpression(const std::string& expr);

    bool balancedBrackets(const std::string& expr);
    void getFirstPairOfNonEmptyBrackets(std::string expr, size_t& start, size_t& end);
    void removeUnnecessarySurroundingBrackets(std::string& expr);

protected:
    ExpressionParser() = default;
    ~ExpressionParser() = default;

private:
    std::string pop(std::list<std::string>& list);
};

CAS_NAMESPACE_END

#endif  //CAS_EXPRESSIONPARSER_H
