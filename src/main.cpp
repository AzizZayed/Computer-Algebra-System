#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)// Windows
#include <fcntl.h>
#include <io.h>
#endif

#include "cas/plot/Function.h"
#include "cas/util/StringUtils.h"

int main() {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)// Windows
    fflush(stdout);
    int result = _setmode(_fileno(stdout), _O_U16TEXT);
    if (result == -1) {
        wprintf(L"Error: Could not set mode in main.cpp.");
        exit(EXIT_FAILURE);
    }
#endif

    cas::Function function = cas::Function::parse("cosx*sinx/tanx");
    wprintf(L"f(x) = %ls", function.stringify().c_str());

    return 0;
}
