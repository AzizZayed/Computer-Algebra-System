#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

struct VertexIn {
    float3 position [[attribute(0)]];
    float4 color [[attribute(1)]];
    //    float3 normal [[attribute(2)]];
};
struct VertexOut {
    float4 position [[position]];
    float4 color;
};

struct WorldView {
    float4x4 perspective;
};

struct Transform {
    float4x4 translate;
    float4x4 rotate;
    float4x4 scale;
};

// ==================== VERTEX SHADER ====================
VertexOut vertex vertexMain(const VertexIn vertexIn [[stage_in]],
                            constant WorldView& worldView [[buffer(15)]],
                            constant Transform& transform [[buffer(16)]]) {

    float4 position = float4(vertexIn.position, 1.0);
    return {
            worldView.perspective * transform.translate * transform.rotate * transform.scale * position,
            vertexIn.color,
    };
}

// ==================== FRAGMENT SHADER ====================
half4 fragment fragmentMain(VertexOut in [[stage_in]]) {
    return half4(in.color.x, in.color.y, in.color.z, in.color.w);
}