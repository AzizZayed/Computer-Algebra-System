//
// Created by Zayed on 9/7/2022.
//

#ifndef CAS_STRINGUTILS_H
#define CAS_STRINGUTILS_H

#include <codecvt>
#include <iostream>
#include <vector>

inline std::wstring toWstring(const std::string& string) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(string);
}

inline std::string toString(const std::wstring& wString) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wString);
}

inline void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

inline std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;

    size_t start = 0;
    size_t end;
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

inline std::vector<std::string> splitFirst(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = str.find(delimiter);
    if (pos != std::string::npos) {
        tokens.push_back(str.substr(0, pos));
        tokens.push_back(str.substr(pos + delimiter.length()));
    }

    return tokens;
}

inline void replaceOnce(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos != std::string::npos)
        str.replace(start_pos, from.length(), to);
}

inline bool contains(const std::string& str, const std::string& subStr) {
    return str.find(subStr) != std::string::npos;
}

inline bool isNumber(const std::string& str) {
    char* p;
    std::strtod(str.c_str(), &p);
    return *p == 0;
}

#endif//CAS_STRINGUTILS_H
