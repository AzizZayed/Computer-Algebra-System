#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) // Windows
#include <io.h>
#include <fcntl.h>
#endif

#include "core/node/Ceil.h"
#include "core/node/Floor.h"
#include "core/node/Round.h"
#include <core/node/Const.h>

#include <cstdio>
#include <cwchar>

int main() {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) // Windows
    fflush(stdout);
    int result = _setmode(_fileno(stdout), _O_U16TEXT);
    if (result == -1) {
        wprintf(L"Error: Could not set mode in main.cpp.");
        exit(EXIT_FAILURE);
    }
#endif

    auto* expression1 = new cas::Floor(cas::Const::PI());
    auto* expression2 = new cas::Ceil(cas::Const::PI());
    auto* expression3 = new cas::Round(cas::Const::PI());
    auto* expression7 = cas::Const::PI()->cos();

    auto* expression4 = new cas::Floor(cas::Const::PHI());
    auto* expression5  = new cas::Ceil(cas::Const::PHI());
    auto* expression6  = new cas::Round(cas::Const::PHI());
    auto* expression8 = cas::Const::PHI()->sin();

    std::wcout << expression1->stringify() << ", ";
    std::wcout << expression2->stringify() << ", ";
    std::wcout << expression3->stringify() << ", ";
    std::wcout << expression4->stringify() << ", ";
    std::wcout << expression5->stringify() << ", ";
    std::wcout << expression6->stringify() << "\n";
    std::wcout << expression7->stringify() << "\n";
    std::wcout << expression8->stringify() << "\n" << std::endl;

    return 0;
}


