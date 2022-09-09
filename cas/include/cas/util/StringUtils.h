//
// Created by Zayed on 9/7/2022.
//

#ifndef CAS_STRINGUTILS_H
#define CAS_STRINGUTILS_H

#include <codecvt>
#include <iostream>
#include <locale>
#include <string>

inline std::wstring toWstring(const std::string& string) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(string);
}

inline std::string toString(const std::wstring& wString) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wString);
}

inline void wPrint(const std::wstring& str) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)// Windows
    std::wcout << str << std::endl;
#else// MacOS & Linux
    std::cout << toString(str) << std::endl;
#endif
}

#endif//CAS_STRINGUTILS_H
