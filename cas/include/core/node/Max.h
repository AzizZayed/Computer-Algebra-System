//
// Created by Abd-El-Aziz Zayed on 2022-09-05.
//

#ifndef CAS_MAX_H
#define CAS_MAX_H

#include "core/CAS.h"
#include "MultipleInputFunction.h"

CAS_NAMESPACE

class Max : public MultipleInputFunction {
public:
    explicit Max(std::vector<Expression*> expressions);
    Max() = delete;
    ~Max() override = default;

    double evaluate(const std::unordered_map<char, double>& variables) override;
    Max* clone() override;
    Expression* simplified() override;
};

CAS_NAMESPACE_END

#endif //CAS_MAX_H
