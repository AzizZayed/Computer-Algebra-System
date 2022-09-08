//
// Created by Zayed on 9/7/2022.
//

#ifndef CAS_STRINGUTILS_H
#define CAS_STRINGUTILS_H

#include <codecvt>
#include <locale>
#include <string>

inline std::wstring toWstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

#endif//CAS_STRINGUTILS_H
