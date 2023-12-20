//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_CAS_H
#define CAS_CAS_H

#define CAS_NAMESPACE namespace cas {
#define CAS_NAMESPACE_END }

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

template <typename Base, typename T>
inline bool instanceof (T * ptr) {
    return dynamic_cast<Base*>(ptr) != nullptr;
}

inline bool isWholeNumber(double number) {
    double intPart;
    return std::modf(number, &intPart) == 0.0;
}

inline bool doubleEquals(double a, double b, double epsilon = 1e-6) {
    double max = std::max(1.0, std::max(std::fabs(a), std::fabs(b)));
    return std::fabs(a - b) <= epsilon * max;
}

#endif  //CAS_CAS_H
