//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_EXPRESSIONPROPERTIES_H
#define CAS_EXPRESSIONPROPERTIES_H

#include "core/CAS.h"
#include "ExpressionType.h"
#include <cstdint>
#include <string>
#include <utility>

CAS_NAMESPACE

class ExpressionProperties {
public:
    ExpressionProperties(ExpressionType type, std::string name, std::string shortName)
    : type(type), order(uint16_t(type)), name(std::move(name)), shortName(std::move(shortName)) {}

    uint16_t getOrder() const { return order; }
    ExpressionType getType() const { return type; }
    std::string getName() const { return name; }
    std::string getShortName() const { return shortName; }

private:
    const uint16_t order;
    const ExpressionType type;
    const std::string name;
    const std::string shortName;
};

CAS_NAMESPACE_END

#endif //CAS_EXPRESSIONPROPERTIES_H
