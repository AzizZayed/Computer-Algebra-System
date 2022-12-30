#include "cas/latex/LatexRenderer.h"
#include "cas/plot/Function.h"

int main() {
    cas::Function function{"2*x^2 + 5*x - 2/3 - acosx"};

    cas::LatexRenderer& renderer = cas::LatexRenderer::getInstance();
    renderer.render(function);
    renderer.cleanup();

    return 0;
}
