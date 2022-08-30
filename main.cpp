#include <iostream>
#include "core/node/Constant.h"

int main() {
    printf("Scratch work here!\n");

    cas::Constant* cs = cas::Constant::PI();
    std::cout << cs->getValue() << std::endl;

    cas::Constant* c = cs->clone();

    delete cs;
    delete c;

    return 0;
}


