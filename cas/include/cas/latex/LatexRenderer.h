//
// Created by Abd-El-Aziz Zayed on 2022-09-10.
//

#ifndef CAS_LATEXRENDERER_H
#define CAS_LATEXRENDERER_H

#include "cas/CAS.h"
#include "cas/node/IRepresentableMath.h"

CAS_NAMESPACE

class LatexRenderer {
public:
    static LatexRenderer& getInstance();
    std::string render(IRepresentableMath* expr, const std::string& filename);

protected:
    LatexRenderer() = default;
    ~LatexRenderer() = default;
};

CAS_NAMESPACE_END

#endif//CAS_LATEXRENDERER_H
