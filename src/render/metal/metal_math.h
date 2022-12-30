//
// Created by Abd-El-Aziz Zayed on 2022-09-30.
//

#ifndef METAL_MATH_H
#define METAL_MATH_H

#include <simd/simd.h>

namespace math {
    simd::float4x4 identity() { return {1.0f}; }

    simd::float4x4 scale(float x, float y, float z) {
        return {
                vector4(x, 0.0f, 0.0f, 0.0f),
                vector4(0.0f, y, 0.0f, 0.0f),
                vector4(0.0f, 0.0f, z, 0.0f),
                vector4(0.0f, 0.0f, 0.0f, 1.0f)};
    }

    simd::float4x4 scale(float sc) {
        return scale(sc, sc, sc);
    }

    simd::float4x4 xRotate(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return {
                vector4(1.0f, 0.0f, 0.0f, 0.0f),
                vector4(0.0f, c, -s, 0.0f),
                vector4(0.0f, s, c, 0.0f),
                vector4(0.0f, 0.0f, 0.0f, 1.0f)};
    }

    simd::float4x4 yRotate(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return {
                vector4(c, 0.0f, s, 0.0f),
                vector4(0.0f, 1.0f, 0.0f, 0.0f),
                vector4(-s, 0.0f, c, 0.0f),
                vector4(0.0f, 0.0f, 0.0f, 1.0f)};
    }

    simd::float4x4 zRotate(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        return {
                vector4(c, -s, 0.0f, 0.0f),
                vector4(s, c, 0.0f, 0.0f),
                vector4(0.0f, 0.0f, 1.0f, 0.0f),
                vector4(0.0f, 0.0f, 0.0f, 1.0f)};
    }

    simd::float4x4 translate(float x, float y, float z) {
        return {
                vector4(1.0f, 0.0f, 0.0f, 0.0f),
                vector4(0.0f, 1.0f, 0.0f, 0.0f),
                vector4(0.0f, 0.0f, 1.0f, 0.0f),
                vector4(x, y, z, 1.0f)};
    }

    simd::float4x4 perspective(float fov, float aspect, float near, float far) {
        float y = 1.0f / tanf(fov * 0.5f);
        float x = y / aspect;
        float z = -(far + near) / (far - near);
        float w = -2.0f * far * near / (far - near);
        return {
                vector4(x, 0.0f, 0.0f, 0.0f),
                vector4(0.0f, y, 0.0f, 0.0f),
                vector4(0.0f, 0.0f, z, -1.0f),
                vector4(0.0f, 0.0f, w, 0.0f)};
    }

}// namespace math

#endif//METAL_MATH_H