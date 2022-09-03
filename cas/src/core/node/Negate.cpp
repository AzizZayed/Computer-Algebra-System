//
// Created by Abd-El-Aziz Zayed on 2022-09-03.
//

#include "core/node/Negate.h"

CAS_NAMESPACE

Negate::Negate(Expression* expression)
: Expression({ExpressionType::NEGATE, "negate", "neg"}), expression(expression)
{
#if DEBUG_CAS
    std::string str = properties.getName();
    printf("%s(...)\n", str.c_str());
#endif

    this->expression->setParent(this);
}

Negate::~Negate()
{
#if DEBUG_CAS
    printf("Destroy cas::Negate\n");
#endif

    delete expression;
}

double Negate::evaluate(const std::unordered_map<char, double>& variables)
{
    return -expression->evaluate(variables);
}

bool Negate::equals(Expression* expr)
{
    if (expr->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(expr);
        return this->expression->equals(negate->getExpression());
    }

    return false;
}

Negate* Negate::clone()
{
    return new Negate(expression->clone());
}

Negate* Negate::derivative(char var)
{
    return new Negate(expression->derivative(var));
}

Expression* Negate::simplified()
{
    auto* simplified = expression->simplified();

    if (simplified->isOfType(ExpressionType::NEGATE)) {
        auto* negate = dynamic_cast<Negate*>(simplified);
        return negate->getExpression()->clone();
    }

    return new Negate(simplified);
}

std::string Negate::latex()
{
    return "-" + expression->latex();
}

std::string Negate::stringify()
{
    return "-(" + expression->stringify() + ")";
}

std::string Negate::text()
{
    return "(-(" + expression->text() + "))";
}

std::string Negate::explicitText()
{
    return properties.getShortName() + "(" + expression->explicitText() + ")";
}

CAS_NAMESPACE_END
