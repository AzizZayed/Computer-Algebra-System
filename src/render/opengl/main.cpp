#include "cas/latex/LatexRenderer.h"
#include "cas/node/Const.h"
#include "cas/node/Power.h"
#include "cas/node/Sqrt.h"
#include "cas/node/Var.h"
#include "cas/node/Ln.h"
#include "cas/node/Sum.h"
#include "cas/node/trig/Sin.h"
#include "cas/node/trig/Cos.h"
#include "cas/node/trig/Tan.h"
#include "cas/plot/Function.h"

int main() {
    cas::Function function{"2*x^2 + 5*x - 2/3 - acosx"};

    cas::LatexRenderer& renderer = cas::LatexRenderer::getInstance();
    renderer.render(function, "f");
    renderer.cleanup();

    return 0;
}
