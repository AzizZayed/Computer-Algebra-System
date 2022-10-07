//
// Created by Abd-El-Aziz Zayed on 2022-09-10.
//

#ifndef CAS_LATEXRENDERER_H
#define CAS_LATEXRENDERER_H

#include "cas/node/IRepresentableMath.h"
#include "cpr/cpr.h"

CAS_NAMESPACE

class LatexRenderer {
public:
    static LatexRenderer& getInstance();
    std::string render(IRepresentableMath& expr, const std::string& name);
    std::string render(const std::string& latex, const std::string& name);
    cpr::Response download(const std::string& url, const std::string& filepath);
    void cleanup();

protected:
    LatexRenderer() = default;
    ~LatexRenderer() = default;

private:
    std::string resFolder = "../res/latex/";
};

CAS_NAMESPACE_END

#endif//CAS_LATEXRENDERER_H
