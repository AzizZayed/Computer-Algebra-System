//
// Created by Abd-El-Aziz Zayed on 2022-10-02.
//

#ifndef METAL_TYPES_H
#define METAL_TYPES_H

#import <simd/simd.h>

typedef struct {
    simd::float3 position;
    simd::float4 color;
} Vertex;

struct WorldView {
    simd::float4x4 perspective;
};

struct Transform {
    simd::float4x4 translate;
    simd::float4x4 rotate;
    simd::float4x4 scale;
};

namespace debug {
    namespace plane {
        const Vertex vertices[] = {
                {vector3(-1.0f, -1.0f, 0.0f), vector4(1.0f, 0.0f, 0.0f, 1.0f)},// red
                {vector3(1.0f, -1.0f, 0.0f), vector4(0.0f, 1.0f, 0.0f, 1.0f)}, // green
                {vector3(-1.0f, 1.0f, 0.0f), vector4(0.0f, 0.0f, 1.0f, 1.0f)}, // blue
                {vector3(1.0f, 1.0f, 0.0f), vector4(0.0f, 0.0f, 0.0f, 1.0f)},  // black
        };
        const uint16_t indices[] = {
                0,
                1,
                2,
                2,
                3,
                1,
        };
        size_t vertexCount = 4;
        size_t indexCount = 6;
    }// namespace plane

    namespace cube {
        const Vertex vertices[] = {
                {vector3(1.0f, 1.0f, 1.0f), vector4(1.0f, 0.0f, 0.0f, 1.0f)},
                {vector3(1.0f, 1.0f, -1.0f), vector4(1.0f, 0.0f, 0.0f, 1.0f)},
                {vector3(1.0f, -1.0f, 1.0f), vector4(1.0f, 0.0f, 0.0f, 1.0f)},
                {vector3(1.0f, -1.0f, -1.0f), vector4(1.0f, 0.0f, 0.0f, 1.0f)},
                {vector3(-1.0f, 1.0f, 1.0f), vector4(0.0f, 1.0f, 0.0f, 1.0f)},
                {vector3(-1.0f, 1.0f, -1.0f), vector4(0.0f, 1.0f, 0.0f, 1.0f)},
                {vector3(-1.0f, -1.0f, 1.0f), vector4(0.0f, 1.0f, 0.0f, 1.0f)},
                {vector3(-1.0f, -1.0f, -1.0f), vector4(0.0f, 1.0f, 0.0f, 1.0f)},
        };
        const uint16_t indices[] = {
                0,
                1,
                2,
                2,
                1,
                3,
                4,
                6,
                5,
                5,
                6,
                7,
                0,
                2,
                4,
                4,
                2,
                6,
                1,
                5,
                3,
                3,
                5,
                7,
                0,
                4,
                1,
                1,
                4,
                5,
                2,
                3,
                6,
                6,
                3,
                7,
        };
        size_t vertexCount = 8;
        size_t indexCount = 36;
    }// namespace cube

}// namespace debug

#endif//METAL_TYPES_H
