//
// Created by Abd-El-Aziz Zayed on 2022-10-25.
//

#ifndef CAS_SURFACE_H
#define CAS_SURFACE_H

#include "Function.h"

template<typename V>// V for vertex
struct Plot {
    bool visible = true;

    static const uint32_t RESOLUTION = 100;
    static const uint32_t SIZE = RESOLUTION + 1;

    static const uint32_t indexCount = RESOLUTION * RESOLUTION * 6;
    static const uint32_t indicesSize = indexCount * sizeof(uint32_t);
    static uint32_t* indices;

    static const uint32_t vertexCount = SIZE * SIZE;
    static const uint32_t verticesSize = vertexCount * sizeof(V);
    V* vertices = new V[vertexCount];

    static void generateIndices() {
        if (indices != nullptr) {
            return;
        }

        indices = new uint32_t[indexCount];
        uint32_t offset = 0;
        for (uint32_t y = 0; y < RESOLUTION; y++) {
            for (uint32_t x = 0; x < RESOLUTION; x++) {
                uint32_t a = y * SIZE + x;
                uint32_t b = a + 1;
                uint32_t c = (y + 1) * SIZE + x;
                uint32_t d = c + 1;

                indices[offset++] = a;
                indices[offset++] = b;
                indices[offset++] = c;

                indices[offset++] = b;
                indices[offset++] = c;
                indices[offset++] = d;
            }
        }
    }

    static void cleanup() {
        if (indices != nullptr) {
            delete[] indices;
            indices = nullptr;
        }
    }
};

CAS_NAMESPACE

template<typename T, typename F>// F: F(xyz, rgba) -> T
class Surface : public Function {
    explicit Surface(std::string strFunction);
    virtual ~Surface() override;

    void update();

private:
    Plot<T> fPlot;
    Plot<T> xDerivativePlot;
    Plot<T> yDerivativePlot;
};

CAS_NAMESPACE_END

#endif//CAS_SURFACE_H
