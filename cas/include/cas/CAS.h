//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_CAS_H
#define CAS_CAS_H

#define CAS_NAMESPACE namespace cas {
#define CAS_NAMESPACE_END }

#include "cas/data/VariableMap.h"
#include <cmath>
#include <cstddef>
#include <unordered_set>

CAS_NAMESPACE

using VarSet = std::unordered_set<char>;

inline size_t nextId() {
    static size_t nextId = 1;
    return nextId++;
}

CAS_NAMESPACE_END

template<typename Base, typename T>
inline bool instanceof (T * ptr) {
    return dynamic_cast<Base*>(ptr) != nullptr;
}

inline bool isWholeNumber(double number) {
    return number == std::trunc(number);
}

#endif//CAS_CAS_H
