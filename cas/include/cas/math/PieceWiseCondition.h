//
// Created by Abd-El-Aziz Zayed on 2022-09-09.
//

#ifndef CAS_PIECEWISECONDITION_H
#define CAS_PIECEWISECONDITION_H

#include "cas/CAS.h"
#include <vector>
#include <unordered_map>

CAS_NAMESPACE

enum ConditionType {
    LessThan,
    LessThanOrEqual,
    GreaterThan,
    GreaterThanOrEqual,
    Equal,
    NotEqual
};

enum OperationType {
    And,
    Or
};

struct Condition {
    char variable;
    ConditionType type;
    double conditionValue;
};

class PieceWiseCondition {
public:
    PieceWiseCondition(const std::vector<Condition>& conditions, std::vector<OperationType> operations);
    PieceWiseCondition() = delete;
    ~PieceWiseCondition() = default;

    bool isMet(const std::unordered_map<char, double>& variables) const;

private:
    std::vector<Condition> conditions;
    std::vector<OperationType> operations;
};

CAS_NAMESPACE_END

#endif//CAS_PIECEWISECONDITION_H
