#include <metal_stdlib>

using namespace metal;

struct VertexIn {
    float3 position [[attribute(0)]];
    float4 color [[attribute(1)]];
//    float3 normal [[attribute(2)]];
};
struct VertexOut {
    float4 position [[position]];
    float4 color;
//    float3 normal;
};

struct WorldView {
    float4x4 perspective;
};

struct Transform {
    float4x4 translate;
    float4x4 rotate;
    float4x4 scale;
};

VertexOut vertex vertexMain( const VertexIn vertexIn [[stage_in]],
                             constant WorldView& worldView [[buffer(15)]],
                             constant Transform& transform [[buffer(16)]])
{
    return {
        worldView.perspective * transform.translate * transform.rotate * transform.scale * float4(vertexIn.position, 1.0),
        vertexIn.color,
//        vertexIn.normal
    };
}
half4 fragment fragmentMain( VertexOut in [[stage_in]]) {
//    float3 l = normalize(float3( 1.0, 1.0, 0.8 ));
//    float3 n = normalize( in.normal );
//    half diffuse = saturate( dot( n, l ) );
//    half ambient = 0.1;
//    float4 illum = (in.color * ambient) + (in.color * diffuse);
//    return half4(illum.x, illum.y, illum.z, illum.w);
//    return half4(in.normal.x, in.normal.y, in.normal.z, 1.0);
    return half4(in.color.x, in.color.y, in.color.z, in.color.w);
}