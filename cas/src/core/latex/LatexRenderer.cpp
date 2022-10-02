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

std::string LatexRenderer::render(IRepresentableMath& expr, const std::string& name) {
    return render(expr.latex(), name);
}

std::string LatexRenderer::render(const std::string& latex, const std::string& name) {
    printf("Rendering latex: %s\n", latex.c_str());
    const std::string baseUrl = R"(https://latex.codecogs.com/png.image?\huge&space;\dpi{300}\bg{black})";
    const std::string url = baseUrl + name + "(x,y)=" + latex;
    printf("Invoking URL: %s", url.c_str());

    std::string filepath = resFolder + name + ".png";
    const cpr::Response& response = download(url.c_str(), filepath.c_str());
    if (response.status_code != 200) {
        printf("Error: %s\n", response.error.message.c_str());
        fprintf(stderr, "Error: %s\n", response.error.message.c_str());
        throw std::runtime_error("Failed to download image");
    }

    return filepath;
}

cpr::Response LatexRenderer::download(const char* url, const char* filepath) {
    std::ofstream ofstream = std::ofstream(filepath);
    return cpr::Download(ofstream, cpr::Url{url});
}

void LatexRenderer::cleanup() {
    for (const auto& entry : std::filesystem::directory_iterator(resFolder)) {
        if (entry.path().filename().string() != "test.png") {
            std::filesystem::remove(entry.path());
        }
    }
}

CAS_NAMESPACE_END