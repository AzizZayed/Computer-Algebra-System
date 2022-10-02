#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)// Windows
#include <fcntl.h>
#include <io.h>
#endif

#include "cas/plot/Function.h"
#include "cas/node/Var.h"
#include "cas/node/Const.h"
#include "cas/node/Power.h"
#include "cas/latex/LatexRenderer.h"
#include <cmath>

int main() {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)// Windows
    fflush(stdout);
    int result = _setmode(_fileno(stdout), _O_U16TEXT);
    if (result == -1) {
        wprintf(L"Error: Could not set mode in main.cpp.");
        exit(EXIT_FAILURE);
    }
#endif

    const char* strFunction = "2*x^2 + 5*x + 2/3 + pi + e + phi";
    cas::Function function = cas::Function::parse(strFunction);

    cas::LatexRenderer& renderer = cas::LatexRenderer::getInstance();
    renderer.render(function, "f");
    renderer.cleanup();
    
    return 0;
}
