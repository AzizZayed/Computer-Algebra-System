//
// Created by Abd-El-Aziz Zayed on 2022-08-25.
//

#ifndef CAS_CAS_H
#define CAS_CAS_H

#define CAS_NAMESPACE namespace cas {
#define CAS_NAMESPACE_END }

#define DEBUG_CAS 0

#include <cmath>

template<typename Base, typename T>
inline bool instanceof (T * ptr) {
    return dynamic_cast<Base*>(ptr) != nullptr;
}

inline bool isWholeNumber(double number) {
    return number == std::trunc(number);
}

#endif//CAS_CAS_H