#include <iostream>
#include "core/node/Constant.h"

int main() {
    printf("Hello, World!\n");
    cas::Constant constant(5);
    cas::Constant constant2(cas::Constant::PHI);
    printf("%s\n", constant2.stringify().c_str());

    cas::Constant constant3 = cas::Constant{cas::Constant::PI};
    printf("%s\n", constant3.stringify().c_str());

    auto* constant4 = new cas::Constant{cas::Constant::E};
    printf("%s\n", constant4->stringify().c_str());

    return 0;
}


