//
// Created by Abd-El-Aziz Zayed on 2022-09-22.
//

#include "cas/latex/LatexRenderer.h"
#include "fmt/printf.h"
#include <filesystem>

CAS_NAMESPACE

LatexRenderer& LatexRenderer::getInstance() {
    static LatexRenderer instance;
    return instance;
}

std::string LatexRenderer::render(IRepresentableMath& expr, const std::string& filename, const std::string& displayName = "z") {
    return render(expr.latex(), filename, displayName);
}

std::string LatexRenderer::render(Function& function) {
    return render(function.latex(), function.getFilename(), function.getName());
}

std::string LatexRenderer::render(const std::string& latex, const std::string& filename, const std::string& displayName = "z") {
    const std::string baseUrl = R"(https://latex.codecogs.com/png.image?\dpi{300}\bg{black})";
    const std::string url = fmt::format("{}{}={}", baseUrl, displayName, latex);
    fmt::print("Invoking URL: {}\n", url);

    std::string filepath = fmt::format("{}/{}{}.png", resFolder, prefix, filename);
    const cpr::Response& response = download(url, filepath);
    if (response.status_code != 200) {
        fmt::fprintf(stderr, "Error: {}\n", response.error.message);
        throw std::runtime_error("Failed to download image");
    }

    fmt::print("Downloaded image to {}\n", filepath);
    return filepath;
}

cpr::Response LatexRenderer::download(const std::string& url, const std::string& filepath) {
    std::ofstream ofstream = std::ofstream(filepath);
    return cpr::Download(ofstream, cpr::Url{url});
}

void LatexRenderer::cleanup() {
    for (const auto& entry: std::filesystem::directory_iterator(resFolder)) {
        if (entry.path().filename().string().starts_with(prefix)) {
            std::filesystem::remove(entry.path());
        }
    }
}

CAS_NAMESPACE_END
