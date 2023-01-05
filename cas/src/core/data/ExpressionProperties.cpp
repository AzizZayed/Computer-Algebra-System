//
// Created by Abd-El-Aziz Zayed on 2022-09-22.
//

#include "cas/data/ExpressionProperties.h"

CAS_NAMESPACE

ExpressionProperties::ExpressionProperties(ExpressionType type, std::string name, std::string shortName)
    : order(static_cast<uint8_t>(type)), type(type), name(std::move(name)), shortName(std::move(shortName)) {}

bool ExpressionProperties::operator==(const ExpressionProperties& other) const {
    return type == other.type && order == other.order && name == other.name && shortName == other.shortName;
}

uint16_t ExpressionProperties::getOrder() const { return order; }

ExpressionType ExpressionProperties::getType() const { return type; }

std::string ExpressionProperties::getName() const { return name; }

std::string ExpressionProperties::getShortName() const { return shortName; }

CAS_NAMESPACE_END