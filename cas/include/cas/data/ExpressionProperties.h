//
// Created by Abd-El-Aziz Zayed on 2022-08-31.
//

#ifndef CAS_EXPRESSIONPROPERTIES_H
#define CAS_EXPRESSIONPROPERTIES_H

#include "ExpressionType.h"
#include <string>

CAS_NAMESPACE

class ExpressionProperties {
public:
    ExpressionProperties(ExpressionType type, std::string name, std::string shortName);

    bool operator==(const ExpressionProperties& other) const;

    [[nodiscard]] uint16_t getOrder() const;
    [[nodiscard]] ExpressionType getType() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getShortName() const;

private:
    const uint16_t order;
    const ExpressionType type;
    const std::string name;
    const std::string shortName;
};

CAS_NAMESPACE_END

#endif  //CAS_EXPRESSIONPROPERTIES_H
