//
// Created by Zayed on 9/7/2022.
//

#ifndef CAS_STRINGUTILS_H
#define CAS_STRINGUTILS_H

#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
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

inline void replaceOnce(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos != std::string::npos)
        str.replace(start_pos, from.length(), to);
}

inline size_t countMatches(const std::string& str, const std::string& subStr) {
    size_t count = 0;
    size_t start = 0;
    while ((start = str.find(subStr, start)) != std::string::npos) {
        count++;
        start += subStr.length();
    }
    return count;
}

inline bool contains(const std::string& str, const std::string& subStr) {
    return str.find(subStr) != std::string::npos;
}

inline bool startsWith(const std::string& str, const std::string& subStr) {
    return str.find(subStr) == 0;
}

inline bool isNumber(const std::string& str) {
    char* p;
    std::strtod(str.c_str(), &p);
    return *p == 0;
}

inline void wPrint(const std::wstring& str) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)// Windows
    std::wcout << str << std::endl;
#else// MacOS & Linux
    std::cout << toString(str) << std::endl;
#endif
}

#endif//CAS_STRINGUTILS_H
