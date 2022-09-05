#include <iostream>
#include "core/node/Abs.h"
#include "core/node/Variable.h"

int main() {
    printf("Scratch work here!\n");

    std::cout << "\u03C0" << ", " << "e, " << "\u03D5" << ", " << std::endl;
    std::cout << "\u230A" << "x" << "\u230B" << std::endl;
    std::cout << "\u2308" << "x" << "\u2309" << std::endl;
    std::cout << "[" << "x" << "]" << std::endl;

    auto* abs = new cas::Abs(new cas::Variable('x'));
    std::cout << abs->latex() << std::endl;
    std::cout << abs->equals(new cas::Constant) << std::endl;


    return 0;
}


