//
// Created by Abd-El-Aziz Zayed on 2022-12-30.
//

#ifndef CAS_VARIABLEMAP_H
#define CAS_VARIABLEMAP_H

#include <cas/CAS.h>
#include <iterator>
#include <stdexcept>
#include <vector>

CAS_NAMESPACE

// TODO redesign to store std::pairs so iterators can be references

struct LetterMap;
struct VariableMapIterator;
class VariableMap;

struct LetterMap {
    static const char LETTER_COUNT = 26;
    char letters = 0;
    double letterMap[LETTER_COUNT] = {};
    bool validLetter[LETTER_COUNT] = {};
};

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
    void clear(char var);
    void clearExceptXY();

    [[nodiscard]] bool contains(char var) const;

    void insert(char var, double value);

    double& operator[](char var);
    [[nodiscard]] double at(char var) const;

    [[nodiscard]] size_t size() const;

    VariableMapIterator begin();
    VariableMapIterator end();

    [[nodiscard]] std::vector<char> variables() const;
    [[nodiscard]] std::vector<double> values() const;
    [[nodiscard]] std::vector<std::pair<char, double>> items() const;

    [[nodiscard]] std::string str() const;

private:
    static std::invalid_argument variableNotFoundException(char var);
    static std::invalid_argument invalidVariableException(char var);

    static bool lowercase(char c, size_t& index);
    static bool uppercase(char c, size_t& index);
    static char toLetter(size_t index, bool isLowercase = true);

    static void strLetterMap(std::stringstream& ss, const LetterMap& letterMap, bool isLowercase = true);

private:
    LetterMap lowercaseVariables;
    LetterMap uppercaseVariables;
};

CAS_NAMESPACE_END

#endif//CAS_VARIABLEMAP_H
