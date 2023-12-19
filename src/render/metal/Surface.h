//
// Created by Abd-El-Aziz Zayed on 2022-12-31.
//

#ifndef COMPUTERALGEBRASYSTEM_SURFACE_H
#define COMPUTERALGEBRASYSTEM_SURFACE_H

#include <string>

#include "Grid.h"
#include "Model.h"

#include "cas/data/VariableMap.h"
#include "cas/latex/LatexRenderer.h"
#include "cas/plot/Function.h"

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import <QuartzCore/QuartzCore.h>

class Surface {
public:
    struct Plot {
        cas::Function* function{};
        Texture* texture{};
        Vertex* vertices{};
        id<MTLBuffer> vertexBuffer{};
        size_t bufferSize{};
        // random color with c++11
        float color[4] = {static_cast<float>(rand()) / RAND_MAX,
                          static_cast<float>(rand()) / RAND_MAX,
                          static_cast<float>(rand()) / RAND_MAX, 1.0f};
        bool render = true;
    };

    explicit Surface(id<MTLDevice> device, const std::string& func, const Grid& grid, cas::VariableMap& variables)
        : func(func), grid(grid), variables(variables) {
        cas::LatexRenderer& latexRenderer = cas::LatexRenderer::getInstance();

        plots[plot].function = new cas::Function(func, (const std::string&) "z", false);
        plots[dx].function = plots[plot].function->simplifiedDerivative('x');
        plots[dy].function = plots[plot].function->simplifiedDerivative('y');

        for (auto& p: plots) {
            if (p.function != nullptr) {
                std::string imagePath = latexRenderer.render(*p.function);
                p.texture = new Texture(device, imagePath);
                p.vertices = new Vertex[grid.vertexCount];
                p.bufferSize = grid.vertexCount * sizeof(Vertex);
                p.vertexBuffer = [device newBufferWithLength:p.bufferSize options:MTLResourceStorageModeShared];
            }
        }
        plots[plot].render = true;
    }

    explicit Surface(id<MTLDevice> device, const char* func, const Grid& grid, cas::VariableMap& variables)
        : Surface(device, std::string(func), grid, variables) {}

    ~Surface() {
        for (Plot& p: plots) {
            if (p.function != nullptr) {
                delete p.function;
                delete p.texture;
                delete[] p.vertices;
                [p.vertexBuffer release];
            }
        }
    }

    static id<MTLBuffer> getIndexBuffer(id<MTLDevice> device, const Grid& grid) {
        static uint32_t* indices;
        static id<MTLBuffer> indexBuffer;

        if (indices == nullptr && indexBuffer == nil) {
            indices = new uint32_t[grid.indexCount];

            uint32_t index = 0;
            for (uint32_t j = 0; j < grid.RESOLUTION; j++) {
                for (uint32_t i = 0; i < grid.RESOLUTION; i++) {
                    uint32_t a = j * grid.WIDTH + i;
                    uint32_t b = a + 1;
                    uint32_t c = (j + 1) * grid.WIDTH + i;
                    uint32_t d = c + 1;

                    indices[index++] = a;
                    indices[index++] = b;
                    indices[index++] = c;

                    indices[index++] = b;
                    indices[index++] = c;
                    indices[index++] = d;
                }
            }

            indexBuffer = [device newBufferWithBytes:indices
                                              length:grid.indexCount * sizeof(uint32_t)
                                             options:MTLResourceStorageModeShared];
            printf("Index buffer created.\n");
        }

        return indexBuffer;
    }

    void update() {
        for (auto& p: plots) {
            if (p.render && p.function != nullptr) {
                updateVertices(p);
            }
        }
    }

    void updateVertices(Plot& p) {
        const double _dx = grid.xStep();
        const double _dy = grid.yStep();
        double x = grid.xMin;
        double y = grid.yMin;

        uint32_t index = 0;
        for (uint32_t j = 0; j < grid.WIDTH; j++) {
            for (uint32_t i = 0; i < grid.WIDTH; i++) {
                variables['x'] = x;
                variables['y'] = y;
                double z = p.function->evaluate(variables);

                auto xf = static_cast<float>(x);
                auto yf = static_cast<float>(y);
                auto zf = static_cast<float>(z);
                p.vertices[index].position = vector3(xf, yf, zf);
                p.vertices[index++].color = vector4(p.color[0], p.color[1], p.color[2], p.color[3]);

                x += _dx;
            }
            y += _dy;
            x = grid.xMin;
        }

        memcpy(p.vertexBuffer.contents, p.vertices, p.bufferSize);
    }

public:
    const std::string func;
    const Grid& grid;
    cas::VariableMap& variables;
    Plot plots[3];
    size_t plot = 0, dx = 1, dy = 2;
};

#endif//COMPUTERALGEBRASYSTEM_SURFACE_H
