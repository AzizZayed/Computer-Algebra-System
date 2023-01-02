//
// Created by Abd-El-Aziz Zayed on 2022-12-30.
//

#include "cas/data/VariableMap.h"
#include <sstream>
#include <string>
#include <utility>
#include <vector>

CAS_NAMESPACE

VariableMap::VariableMap(const std::initializer_list<std::pair<char, double>>& list) {
    for (const auto& [var, value]: list) {
        insert(var, value);
    }
}

void VariableMap::insert(char var, double value) {
    size_t index = 0;
    if (lowercase(var, index)) {
        lowercaseVariables.letterMap[index] = value;
        if (!lowercaseVariables.validLetter[index]) {
            lowercaseVariables.validLetter[index] = true;
            lowercaseVariables.letters++;
        }
    } else if (uppercase(var, index)) {
        uppercaseVariables.letterMap[index] = value;
        if (!uppercaseVariables.validLetter[index]) {
            uppercaseVariables.validLetter[index] = true;
            uppercaseVariables.letters++;
        }
    } else {
        throw std::invalid_argument("Variable is not a letter.");
    }
}

double& VariableMap::operator[](char var) {
    size_t index = 0;
    if (lowercase(var, index)) {
        if (lowercaseVariables.validLetter[index]) {
            return lowercaseVariables.letterMap[index];
        }
        throw variableNotFoundException(var);
    } else if (uppercase(var, index)) {
        if (uppercaseVariables.validLetter[index]) {
            return uppercaseVariables.letterMap[index];
        }
        throw variableNotFoundException(var);
    }
    throw std::invalid_argument("Variable is not a letter.");
}

double VariableMap::at(char var) const {
    size_t index = 0;
    if (lowercase(var, index)) {
        if (lowercaseVariables.validLetter[index]) {
            return lowercaseVariables.letterMap[index];
        }
        throw variableNotFoundException(var);
    } else if (uppercase(var, index)) {
        if (uppercaseVariables.validLetter[index]) {
            return uppercaseVariables.letterMap[index];
        }
        throw variableNotFoundException(var);
    }
    throw std::invalid_argument("Variable is not a letter.");
}

VariableMapIterator VariableMap::begin() {
    return {*this, 'a'};
}

VariableMapIterator VariableMap::end() {
    return {*this, 'Z' + 1};
}

std::vector<char> VariableMap::variables() const {
    std::vector<char> vars;
    vars.reserve(lowercaseVariables.letters + uppercaseVariables.letters);

    for (size_t i = 0; i < LetterMap::LETTER_COUNT; i++) {
        if (lowercaseVariables.validLetter[i]) {
            vars.push_back(toLetter(i));
        }
    }
    for (size_t i = 0; i < LetterMap::LETTER_COUNT; i++) {
        if (uppercaseVariables.validLetter[i]) {
            vars.push_back(toLetter(i, false));
        }
    }

    return vars;
}

std::vector<double> VariableMap::values() const {
    std::vector<double> values;
    values.reserve(lowercaseVariables.letters + uppercaseVariables.letters);

    for (size_t i = 0; i < LetterMap::LETTER_COUNT; i++) {
        if (lowercaseVariables.validLetter[i]) {
            values.push_back(lowercaseVariables.letterMap[i]);
        }
    }
    for (size_t i = 0; i < LetterMap::LETTER_COUNT; i++) {
        if (uppercaseVariables.validLetter[i]) {
            values.push_back(uppercaseVariables.letterMap[i]);
        }
    }

    return values;
}

std::vector<std::pair<char, double>> VariableMap::items() const {
    std::vector<std::pair<char, double>> items;
    items.reserve(lowercaseVariables.letters + uppercaseVariables.letters);

    for (size_t i = 0; i < LetterMap::LETTER_COUNT; i++) {
        if (lowercaseVariables.validLetter[i]) {
            items.emplace_back(toLetter(i), lowercaseVariables.letterMap[i]);
        }
    }
    for (size_t i = 0; i < LetterMap::LETTER_COUNT; i++) {
        if (uppercaseVariables.validLetter[i]) {
            items.emplace_back(toLetter(i, false), uppercaseVariables.letterMap[i]);
        }
    }

    return items;
}

bool VariableMap::contains(char var) const {
    size_t index = 0;
    if (lowercase(var, index)) {
        return lowercaseVariables.validLetter[index];
    } else if (uppercase(var, index)) {
        return uppercaseVariables.validLetter[index];
    }
    throw variableNotFoundException(var);
}

void VariableMap::clear() {
    lowercaseVariables = {};
    uppercaseVariables = {};
}

std::string VariableMap::str() const {
    std::stringstream ss;

    ss << "Variable Map: {\n";

    strLetterMap(ss, lowercaseVariables);
    strLetterMap(ss, uppercaseVariables, false);

    ss << "}";
    return ss.str();
}

std::invalid_argument VariableMap::variableNotFoundException(char var) {
    return std::invalid_argument("Variable " + std::string(1, var) + " is not in the map.");
}

bool VariableMap::lowercase(char c, size_t& index) {
    bool isLowercase = c >= 'a' && c <= 'z';

    if (isLowercase) {
        index = c - 'a';
    }

    return isLowercase;
}

bool VariableMap::uppercase(char c, size_t& index) {
    bool isUppercase = c >= 'A' && c <= 'Z';

    if (isUppercase) {
        index = c - 'A';
    }

    return isUppercase;
}

char VariableMap::toLetter(size_t index, bool isLowercase) {
    size_t letter = isLowercase ? 'a' + index : 'A' + index;
    return static_cast<char>(letter);
}

void VariableMap::strLetterMap(std::stringstream& ss, const LetterMap& letterMap, bool isLowercase) {
    if (isLowercase) {
        ss << "\tLowercase Variables: ";
    } else {
        ss << "\tUppercase Variables: ";
    }
    ss << '(' << static_cast<int>(letterMap.letters) << ") [";

    int letters = 0;
    for (size_t i = 0; i < LetterMap::LETTER_COUNT; ++i) {
        if (letterMap.validLetter[i]) {
            letters++;
            ss << toLetter(i, isLowercase) << '=' << letterMap.letterMap[i];
            if (letters < letterMap.letters) {
                ss << ", ";
            }
        }
    }
    ss << "]\n";
}

VariableMapIterator::VariableMapIterator(VariableMap& map, char letter) : variableMap(map), letter(letter) {}

VariableMapIterator& VariableMapIterator::operator++() {
    do {
        letter++;
        if (letter == 'z' + 1) {
            letter = 'A';
        }
    } while ((letter >= 'a' && letter <= 'z' || letter >= 'A' && letter <= 'Z') &&
             !variableMap.contains(letter));

    return *this;
}

VariableMapIterator VariableMapIterator::operator++(int) {
    VariableMapIterator tmp = *this;
    ++(*this);
    return tmp;
}

bool VariableMapIterator::operator==(const VariableMapIterator& other) const {
    return letter == other.letter;
}

bool VariableMapIterator::operator!=(const VariableMapIterator& other) const {
    return letter != other.letter;
}

VariableMapIterator::value_type VariableMapIterator::operator*() {
    if (!variableMap.contains(letter)) {
        ++(*this);
    }

    double value = variableMap.at(letter);
    return std::make_pair(letter, value);
}

CAS_NAMESPACE_END