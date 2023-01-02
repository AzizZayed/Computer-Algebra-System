//
// Created by Abd-El-Aziz Zayed on 2022-12-30.
//

#ifndef VARIABLEMAP_H
#define VARIABLEMAP_H


#include <cas/CAS.h>
#include <iterator>
#include <stdexcept>

CAS_NAMESPACE

struct LetterMap {
    static const char LETTER_COUNT = 26;
    char letters = 0;
    double letterMap[LETTER_COUNT] = {};
    bool validLetter[LETTER_COUNT] = {};
};

class VariableMap;

struct VariableMapIterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = char;
    using value_type = std::pair<char, double>;
    using pointer = value_type*;
    using reference = value_type&;

    VariableMapIterator(VariableMap& map, char letter);

    VariableMapIterator& operator++();
    VariableMapIterator operator++(int);

    bool operator==(const VariableMapIterator& other) const;
    bool operator!=(const VariableMapIterator& other) const;

    value_type operator*();

private:
    VariableMap& variableMap;
    char letter;
};

class VariableMap {
public:
    VariableMap() = default;
    VariableMap(const VariableMap&) = delete;
    VariableMap(VariableMap&&) = default;
    VariableMap(const std::initializer_list<std::pair<char, double>>& list);
    ~VariableMap() = default;

    VariableMap& operator=(VariableMap&&) = default;
    VariableMap& operator=(const VariableMap&) = delete;

    void clear();

    [[nodiscard]] bool contains(char var) const;

    void insert(char var, double value);

    double& operator[](char var);
    double at(char var) const;

    VariableMapIterator begin();
    VariableMapIterator end();

    [[nodiscard]] std::vector<char> variables() const;
    [[nodiscard]] std::vector<double> values() const;
    [[nodiscard]] std::vector<std::pair<char, double>> items() const;

    [[nodiscard]] std::string str() const;

private:
    static std::invalid_argument variableNotFoundException(char var);

    static bool lowercase(char c, size_t& index);
    static bool uppercase(char c, size_t& index);
    static char toLetter(size_t index, bool isLowercase = true);

    static void strLetterMap(std::stringstream& ss, const LetterMap& letterMap, bool isLowercase = true);

private:
    LetterMap lowercaseVariables;
    LetterMap uppercaseVariables;
};

CAS_NAMESPACE_END

#endif//VARIABLEMAP_H
