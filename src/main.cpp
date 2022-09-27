#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)// Windows
#include <fcntl.h>
#include <io.h>
#endif

#include "cas/node/Ceil.h"
#include "cas/node/Const.h"
#include "cas/node/Floor.h"
#include "cas/node/Round.h"
#include "cas/node/Sum.h"
#include "cas/node/Var.h"
#include "cas/node/trig/Cos.h"
#include "cas/node/trig/Sin.h"
#include "cas/util/StringUtils.h"
#include "cas/latex/LatexRenderer.h"
#include "cas/data/ExpressionParser.h"

int main() {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)// Windows
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
    auto* expression7 = cas::Const::PI()->cos()->subtract(cas::Const::PI()->sin());

    auto* expression4 = new cas::Floor(cas::Const::PHI());
    auto* expression5 = new cas::Ceil(cas::Const::PHI());
    auto* expression6 = new cas::Round(cas::Const::PHI());
    auto* expression8 = cas::Const::PHI()->sin();

    wPrint(expression1->stringify());
    wPrint(expression2->stringify());
    wPrint(expression3->stringify());
    wPrint(expression4->stringify());
    wPrint(expression5->stringify());
    wPrint(expression6->stringify());
    wPrint(expression7->stringify());
    wPrint(expression8->stringify());

    return 0;
}
