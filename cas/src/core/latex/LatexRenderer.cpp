//
// Created by Abd-El-Aziz Zayed on 2022-09-22.
//

#include "cas/latex/LatexRenderer.h"
#include "stdexcept"

CAS_NAMESPACE

LatexRenderer& LatexRenderer::getInstance() {
    static LatexRenderer instance;
    return instance;
}

std::string LatexRenderer::render(IRepresentableMath* expr, const std::string& filename) {

    std::string string = "cd ../latex-rendering && "
                         "./gradlew run --args=\"" + expr->latex() + " " + filename + "\"";

    int errorCode = system(string.c_str());
    if (errorCode != 0) {
        throw std::runtime_error("Failed to render latex");
    }

    return "../res/" + filename + ".png";
}

CAS_NAMESPACE_END